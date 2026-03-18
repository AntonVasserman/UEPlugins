// Copyright Anton Vasserman, All Rights Reserved.


#include "Animation/AnimNotifies/AV_AnimNotify_SendGameplayEventsBySweep.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AVUtilitiesGameplayAbilities.h"
#include "Animation/AnimSequenceBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif // WITH_EDITOR

void UAV_AnimNotify_SendGameplayEventsBySweep::SendEvents(AActor* Owner, TArray<FHitResult> Hits)
{
	// If we can't find the Ability Component we won't throw, we will just not send events
	const UAbilitySystemComponent* AbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Owner);
	if (!IsValid(AbilitySystem))
	{
		AV_LOG_UTILSGAS_EXTENDED(Warning, "Couldn't find AbilitySystemComponent on for Actor: %s", *Owner->GetFullName());
		return;
	}
	
	if (Hits.IsEmpty())
	{
		return;
	}
	
	if (bSendSingleEventToOwner)
	{
		const FGameplayEffectContextHandle EffectContext = AbilitySystem->MakeEffectContext();
		FGameplayEventData Payload;
		Payload.ContextHandle = EffectContext;
		Payload.Instigator = Owner;
		
		for (const FGameplayTag& GameplayEventForOwner : GameplayEventsForOwner)
		{
			if (GameplayEventForOwner == FGameplayTag::EmptyTag) continue;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, GameplayEventForOwner, Payload);	
		}
	}
	
	for (FHitResult Hit : Hits)
	{
		if (!IsValid(Hit.GetActor())) continue;
		
		FGameplayEffectContextHandle EffectContext = AbilitySystem->MakeEffectContext();
		EffectContext.AddHitResult(Hit);
		
		FGameplayEventData Payload;
		Payload.ContextHandle = EffectContext;
		Payload.Instigator = Owner;
		Payload.Target = Hit.GetActor();
		
		if (!bSendSingleEventToOwner)
		{
			for (const FGameplayTag& GameplayEventForOwner : GameplayEventsForOwner)
			{
				if (GameplayEventForOwner == FGameplayTag::EmptyTag) continue;
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, GameplayEventForOwner, Payload);	
			}
		}
		
		for (const FGameplayTag& GameplayEventForHitActor : GameplayEventsForHitActor)
		{
			if (GameplayEventForHitActor == FGameplayTag::EmptyTag) continue;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Hit.GetActor(), GameplayEventForHitActor, Payload);	
		}
	}
}

//~ UAnimNotify

FString UAV_AnimNotify_SendGameplayEventsBySweep::GetNotifyName_Implementation() const
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

	FString Name = FString::Printf(TEXT("Send Gameplay Events by Trace: %s, with Collision: %s"), *TraceString, *CollisionsJoined);

	// Keep it timeline-friendly
	if (constexpr int32 MaxLen = 80;
		Name.Len() > MaxLen)
	{
		Name = Name.Left(MaxLen - 3) + TEXT("...");
	}

	return Name;
}

void UAV_AnimNotify_SendGameplayEventsBySweep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
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
	
	SendEvents(Owner, Hits);
}

//~ UObject

#if WITH_EDITOR

EDataValidationResult UAV_AnimNotify_SendGameplayEventsBySweep::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (GameplayEventsForOwner.Num() == 0 && GameplayEventsForHitActor.Num() == 0)
	{
		Context.AddError(FText::FromString(TEXT("GameplayEvents can't be Empty, at least one (Owner/HitActor) must be set with a non empty tag")));
		 Result = EDataValidationResult::Invalid;
	}
	
	bool bTagFound = false;
	
	for (const FGameplayTag& GameplayEventTag : GameplayEventsForOwner)
	{
		if (bTagFound) break;
		
		if (GameplayEventTag == FGameplayTag::EmptyTag) continue;
		bTagFound = true;
	}
	
	for (const FGameplayTag& GameplayEventTag : GameplayEventsForHitActor)
	{
		if (bTagFound) break;
		
		if (GameplayEventTag == FGameplayTag::EmptyTag) continue;
		bTagFound = true;
	}
	
	if (bTagFound == false)
	{
		Context.AddError(FText::FromString(TEXT("GameplayEventTags can't be Empty, at least one (Owner/HitActor) must be set")));
		Result = EDataValidationResult::Invalid;
	}
	
	return Result;
}

#endif // WITH_EDITOR
