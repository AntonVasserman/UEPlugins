// Copyright Anton Vasserman, All Rights Reserved.


#include "Animation/AnimNotifies/AV_AnimNotify_ApplyGameplayEffect.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AVUtilitiesGameplayAbilities.h"
#include "Components/SkeletalMeshComponent.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif // WITH_EDITOR

//~ UAnimNotify

FString UAV_AnimNotify_ApplyGameplayEffect::GetNotifyName_Implementation() const
{
	FString GameplayEffectClassName = TEXT("None");
	if (GameplayEffectClass)
	{
		GameplayEffectClassName = GameplayEffectClass->GetName();
	}
	
	return FString::Printf(TEXT("Try Apply Gameplay Effect: %s at Level: %f"), *GameplayEffectClassName, GameplayEffectLevel);
}

void UAV_AnimNotify_ApplyGameplayEffect::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
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
	checkf(GameplayEffectClass, TEXT("%s::%hs: GameplayEffectClass uninitialized"), *GetClass()->GetName(), __FUNCTION__);

	const FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, GameplayEffectLevel, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), AbilitySystemComponent);
}

#if WITH_EDITOR
EDataValidationResult UAV_AnimNotify_ApplyGameplayEffect::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (GameplayEffectClass == nullptr)
	{
		Context.AddError(FText::FromString(TEXT("GameplayEffectClass isn't set")));
		Result = EDataValidationResult::Invalid;
	}
	
	return Result;
}
#endif // WITH_EDITOR
