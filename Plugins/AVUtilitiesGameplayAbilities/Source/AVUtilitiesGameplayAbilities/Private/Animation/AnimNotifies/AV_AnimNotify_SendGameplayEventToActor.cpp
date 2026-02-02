// Copyright Anton Vasserman, All Rights Reserved.


#include "Animation/AnimNotifies/AV_AnimNotify_SendGameplayEventToActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AVUtilitiesGameplayAbilities.h"
#include "Components/SkeletalMeshComponent.h"
#include "Misc/DataValidation.h"

FString UAV_AnimNotify_SendGameplayEventToActor::GetNotifyName_Implementation() const
{
	return FString::Printf(TEXT("Send Gameplay Event to Actor with Tag: %s"), *EventTag.ToString());
}

void UAV_AnimNotify_SendGameplayEventToActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	AActor* Actor = Cast<AActor>(MeshComp->GetOwner());
	const UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);

	// If we can't find the Component we won't throw, we will just not apply the effect
	if (AbilitySystemComponent == nullptr)
	{
		UE_LOG(LogAV_UtilitiesGameplayAbilities, Warning, TEXT("Couldn't find AbilitySystemComponent on for Actor: %s"), *Actor->GetFullName());
		return;
	}

	checkf(AbilitySystemComponent, TEXT("%s: AbilitySystemComponent uninitialized"), __FUNCTIONW__);
	
	FGameplayEventData Payload;
	Payload.Instigator = AbilitySystemComponent->GetAvatarActor();
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Actor, EventTag, Payload);
}

#if WITH_EDITOR
EDataValidationResult UAV_AnimNotify_SendGameplayEventToActor::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (EventTag == FGameplayTag::EmptyTag)
	{
		Context.AddError(FText::FromString(TEXT("GameplayTag can't be left Empty")));
		Result = EDataValidationResult::Invalid;
	}
	
	return Result;
}
#endif // WITH_EDITOR
