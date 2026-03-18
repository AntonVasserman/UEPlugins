// Copyright Anton Vasserman, All Rights Reserved.


#include "Animation/AnimNotifies/AV_AnimNotify_ApplyGameplayEffectsBySweep.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AVUtilitiesGameplayAbilities.h"
#include "Animation/AnimSequenceBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif // WITH_EDITOR

//~ UAnimNotify

void UAV_AnimNotify_ApplyGameplayEffectsBySweep::ApplyEffects(AActor* Owner, TArray<FHitResult> Hits)
{
	// If we can't find the Ability Component we won't throw, we will just not apply the effect
	UAbilitySystemComponent* AbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Owner);
	if (!IsValid(AbilitySystem))
	{
		AV_LOG_UTILSGAS_EXTENDED(Warning, "Couldn't find AbilitySystemComponent on for Actor: %s", *Owner->GetFullName());
		return;
	};
	
	for (const FAV_AnimNotifyGameplayEffectPayload& GameplayEffect : GameplayEffects)
	{
		checkf(GameplayEffect.Class, TEXT("%s::%hs: GameplayEffectClass uninitialized"), *GetClass()->GetName(), __FUNCTION__);

		const FGameplayEffectContextHandle ContextHandle = AbilitySystem->MakeEffectContext();
		const FGameplayEffectSpecHandle SpecHandle = AbilitySystem->MakeOutgoingSpec(GameplayEffect.Class, GameplayEffect.Level, ContextHandle);
	
		if (GameplayEffect.bSetByCallerMagnitudeCalculation)
		{
			for (const TTuple<FGameplayTag, float>& SetByCallerMagnitude : GameplayEffect.SetByCallerMagnitudes)
			{
				SpecHandle.Data->SetSetByCallerMagnitude(SetByCallerMagnitude.Key, SetByCallerMagnitude.Value);
			}
		}
	
		for (FHitResult Hit : Hits)
		{
			if (!IsValid(Hit.GetActor())) continue;
		
			UAbilitySystemComponent* TargetAbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Hit.GetActor());
			if (!IsValid(TargetAbilitySystem)) continue;
		
			AbilitySystem->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetAbilitySystem);
		}
	}
}

FString UAV_AnimNotify_ApplyGameplayEffectsBySweep::GetNotifyName_Implementation() const
{
	const UEnum* ChannelEnum = StaticEnum<ECollisionChannel>();
	const FString TraceString = ChannelEnum ? ChannelEnum->GetNameStringByValue(SweepParams.TraceChannel) : TEXT("UnknownTrace");

	TArray<FString> CollisionStrings;
	CollisionStrings.Reserve(SweepParams.CollisionChannelsToSweep.Num());
	for (const ECollisionChannel CollisionChannel : SweepParams.CollisionChannelsToSweep)
	{
		CollisionStrings.Add(ChannelEnum ? ChannelEnum->GetNameStringByValue(CollisionChannel) : TEXT("UnknownChannel"));
	}

	const FString CollisionsJoined = CollisionStrings.Num() > 0 ? FString::Join(CollisionStrings, TEXT("|")) : TEXT("None");

	FString Name = FString::Printf(TEXT("Apply %d Gameplay Effects by Trace: %s, with Collision: %s"), GameplayEffects.Num(), *TraceString, *CollisionsJoined);

	// Keep it timeline-friendly
	if (constexpr int32 MaxLen = 80;
		Name.Len() > MaxLen)
	{
		Name = Name.Left(MaxLen - 3) + TEXT("...");
	}

	return Name;
}

void UAV_AnimNotify_ApplyGameplayEffectsBySweep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	// Check for validity of mesh and owner
	if (!IsValid(MeshComp)) return;

	AActor* Owner = MeshComp->GetOwner();
	if (!IsValid(Owner)) return;
	
	const TArray<FHitResult> Hits = UAV_UtilitiesGameplayAbilitiesStatics::PerformSweep(Owner, MeshComp, SweepParams);
	
	// Sweep for debugging purposes but don't run actual logic inside the editor...
	if (!IsValid(MeshComp->GetWorld()) || !MeshComp->GetWorld()->IsGameWorld())
	{
		return;
	}
	
	ApplyEffects(Owner, Hits);
}

//~ UObject

#if WITH_EDITOR
EDataValidationResult UAV_AnimNotify_ApplyGameplayEffectsBySweep::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	for (int i = 0; i < GameplayEffects.Num(); ++i)
	{
		const FAV_AnimNotifyGameplayEffectPayload& GameplayEffect = GameplayEffects[i];
		
		if (GameplayEffect.Class == nullptr)
		{
			Context.AddError(FText::FromString(TEXT("GameplayEffectClass isn't set")));
			Result = EDataValidationResult::Invalid;
		}
	}
	
	return Result;
}
#endif // WITH_EDITOR