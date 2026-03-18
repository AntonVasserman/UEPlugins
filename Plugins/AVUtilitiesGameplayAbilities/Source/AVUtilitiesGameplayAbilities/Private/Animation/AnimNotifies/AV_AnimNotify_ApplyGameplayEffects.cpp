// Copyright Anton Vasserman, All Rights Reserved.


#include "Animation/AnimNotifies/AV_AnimNotify_ApplyGameplayEffects.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AVUtilitiesGameplayAbilities.h"
#include "AV_UtilitiesGameplayAbilitiesStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif // WITH_EDITOR

FString UAV_AnimNotify_ApplyGameplayEffects::GetNotifyName_Implementation() const
{
	return FString::Printf(TEXT("Apply %d Gameplay Effects"), GameplayEffects.Num());
}

void UAV_AnimNotify_ApplyGameplayEffects::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	// Don't run the actual logic inside the editor...
	if (!IsValid(MeshComp) || !IsValid(MeshComp->GetWorld()) || !MeshComp->GetWorld()->IsGameWorld())
	{
		return;
	}
	
	AActor* Actor = Cast<AActor>(MeshComp->GetOwner());
	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);

	// If we can't find the Component we won't throw, we will just not apply the effect
	if (AbilitySystemComponent == nullptr)
	{
		AV_LOG_UTILSGAS_EXTENDED(Warning, "Couldn't find AbilitySystemComponent on for Actor: %s", *Actor->GetFullName());
		return;
	}

	checkf(AbilitySystemComponent, TEXT("%hs: AbilitySystemComponent uninitialized"), __FUNCTION__);
	
	for (int i = 0; i < GameplayEffects.Num(); ++i)
	{
		const FAV_AnimNotifyGameplayEffectPayload& GameplayEffect = GameplayEffects[i];
		
		checkf(GameplayEffect.Class, TEXT("%s::%hs: GameplayEffectClass at index: %d uninitialized"), *GetClass()->GetName(), __FUNCTION__, i);
		
		const FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect.Class, GameplayEffect.Level, ContextHandle);
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

#if WITH_EDITOR
EDataValidationResult UAV_AnimNotify_ApplyGameplayEffects::IsDataValid(FDataValidationContext& Context) const
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
