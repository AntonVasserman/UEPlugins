// Copyright Anton Vasserman, All Rights Reserved.


#include "Animation/AnimNotifies/AV_AnimNotifyState_AddGameplayTagASC.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AVUtilitiesGameplayAbilities.h"
#include "Components/SkeletalMeshComponent.h"
#include "Misc/DataValidation.h"

//~ UAnimNotifyState

FString UAV_AnimNotifyState_AddGameplayTagASC::GetNotifyName_Implementation() const
{
	return FString::Printf(TEXT("Add Gameplay Tag: %s to Ability System Component, with Count: %d"), *GameplayTag.GetTagName().ToString(), Count);
}

void UAV_AnimNotifyState_AddGameplayTagASC::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	AActor* Actor = Cast<AActor>(MeshComp->GetOwner());
	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);

	// If we can't find the Component we won't throw, we will just not apply the effect
	if (AbilitySystemComponent == nullptr)
	{
		UE_LOG(LogAV_UtilitiesGameplayAbilities, Warning, TEXT("Couldn't find AbilitySystemComponent on for Actor: %s"), *Actor->GetFullName());
		return;
	}

	checkf(AbilitySystemComponent, TEXT("%s: AbilitySystemComponent uninitialized"), __FUNCTIONW__);
	
	AbilitySystemComponent->AddLooseGameplayTag(GameplayTag, Count);
}

void UAV_AnimNotifyState_AddGameplayTagASC::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	
	if (bRemoveOnExit)
	{
		AActor* Actor = Cast<AActor>(MeshComp->GetOwner());
		UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);

		// If we can't find the Component we won't throw, we will just not apply the effect
		if (AbilitySystemComponent == nullptr)
		{
			UE_LOG(LogAV_UtilitiesGameplayAbilities, Warning, TEXT("Couldn't find AbilitySystemComponent on for Actor: %s"), *Actor->GetFullName());
			return;
		}

		checkf(AbilitySystemComponent, TEXT("%s: AbilitySystemComponent uninitialized"), __FUNCTIONW__);
		
		AbilitySystemComponent->RemoveLooseGameplayTag(GameplayTag, Count);
	}
}

#if WITH_EDITOR
EDataValidationResult UAV_AnimNotifyState_AddGameplayTagASC::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (GameplayTag == FGameplayTag::EmptyTag)
	{
		Context.AddError(FText::FromString(TEXT("GameplayTag can't be left Empty")));
		Result = EDataValidationResult::Invalid;
	}
	
	if (Count == 0)
	{
		Context.AddError(FText::FromString(TEXT("Count can't be set to 0")));
		Result = EDataValidationResult::Invalid;
	}

	return Result;
}
#endif // WITH_EDITOR
