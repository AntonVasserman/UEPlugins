// Copyright Anton Vasserman, All Rights Reserved.


#include "Animation/AnimNotifies/AV_AnimNotify_UpdateGameplayTagASC.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AVUtilitiesGameplayAbilities.h"
#include "Components/SkeletalMeshComponent.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif // WITH_EDITOR

//~ UAnimNotify

FString UAV_AnimNotify_UpdateGameplayTagASC::GetNotifyName_Implementation() const
{
	return FString::Printf(TEXT("Try %s Gameplay Tag: %s"), *StaticEnum<EAV_GameplayTagUpdateType>()->GetNameStringByValue(static_cast<int64>(OperationType)), *GameplayTag.ToString());
}

void UAV_AnimNotify_UpdateGameplayTagASC::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	AActor* Actor = Cast<AActor>(MeshComp->GetOwner());
	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);

	// If we can't find the Component we won't throw, we will just not apply the effect
	if (AbilitySystemComponent == nullptr)
	{
		AV_LOG_UTILSGAS_EXTENDED(Warning, "Couldn't find AbilitySystemComponent on for Actor: %s", *Actor->GetFullName());
		return;
	}

	checkf(AbilitySystemComponent, TEXT("%hs: AbilitySystemComponent uninitialized"), __FUNCTION__);
	
	switch (OperationType)
	{
	case EAV_GameplayTagUpdateType::Set:
		AbilitySystemComponent->SetLooseGameplayTagCount(GameplayTag, 1);
		break;
	case EAV_GameplayTagUpdateType::Remove:
		AbilitySystemComponent->RemoveLooseGameplayTag(GameplayTag);
		break;
	default:
		checkNoEntry();
		break;
	}
}

//~ UObject

#if WITH_EDITOR
EDataValidationResult UAV_AnimNotify_UpdateGameplayTagASC::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (GameplayTag == FGameplayTag::EmptyTag)
	{
		Context.AddError(FText::FromString(TEXT("GameplayTag can't be left Empty")));
		Result = EDataValidationResult::Invalid;
	}
	
	return Result;
}
#endif // WITH_EDITOR
