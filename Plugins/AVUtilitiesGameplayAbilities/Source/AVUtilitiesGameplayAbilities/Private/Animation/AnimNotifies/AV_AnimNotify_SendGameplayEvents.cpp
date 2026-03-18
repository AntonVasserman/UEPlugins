// Copyright Anton Vasserman, All Rights Reserved.


#include "Animation/AnimNotifies/AV_AnimNotify_SendGameplayEvents.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AVUtilitiesGameplayAbilities.h"
#include "Components/SkeletalMeshComponent.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif // WITH_EDITOR

//~ UAnimNotify

FString UAV_AnimNotify_SendGameplayEvents::GetNotifyName_Implementation() const
{
	return FString::Printf(TEXT("Send %d Gameplay Events to Actor (to Self)"), EventTags.Num());
}

void UAV_AnimNotify_SendGameplayEvents::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	AActor* Actor = Cast<AActor>(MeshComp->GetOwner());
	const UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);

	// If we can't find the Component we won't throw, we will just not apply the effect
	if (AbilitySystemComponent == nullptr)
	{
		AV_LOG_UTILSGAS_EXTENDED(Warning, "Couldn't find AbilitySystemComponent on for Actor: %s", *Actor->GetFullName());
		return;
	}

	checkf(AbilitySystemComponent, TEXT("%hs: AbilitySystemComponent uninitialized"), __FUNCTION__);
	
	FGameplayEventData Payload;
	Payload.Instigator = AbilitySystemComponent->GetAvatarActor();
	
	for (const FGameplayTag& EventTag : EventTags)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Actor, EventTag, Payload);
	}
}

//~ UObject

#if WITH_EDITOR
EDataValidationResult UAV_AnimNotify_SendGameplayEvents::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	for (int i = 0; i < EventTags.Num(); ++i)
	{
		const FGameplayTag EventTag = EventTags[i];
		
		if (EventTag == FGameplayTag::EmptyTag)
		{
			Context.AddError(FText::FromString(FString::Printf(TEXT("GameplayTag at index: '%d' can't be left Empty"), i)));
			Result = EDataValidationResult::Invalid;
		}
	}
	
	return Result;
}
#endif // WITH_EDITOR