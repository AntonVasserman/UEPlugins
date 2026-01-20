// Copyright Anton Vasserman, All Rights Reserved.

#include "StateTrees/Tasks/AV_ApplyGameplayEffectStateTreeTask.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "StateTreeExecutionContext.h"

FAV_ApplyGameplayEffectStateTreeTask::FAV_ApplyGameplayEffectStateTreeTask()
{
	bShouldCallTick = false;
}

//~ FStateTreeTaskCommonBase

EStateTreeRunStatus FAV_ApplyGameplayEffectStateTreeTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	if (InstanceData.AbilitySystemComponent == nullptr)
	{
		return EStateTreeRunStatus::Failed;
	}
	
	if (InstanceData.GameplayEffectClass == nullptr)
	{
		return EStateTreeRunStatus::Failed;
	}

	const FGameplayEffectContextHandle ContextHandle = InstanceData.AbilitySystemComponent->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = InstanceData.AbilitySystemComponent->MakeOutgoingSpec(InstanceData.GameplayEffectClass, InstanceData.GameplayEffectLevel, ContextHandle);
	InstanceData.AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), InstanceData.AbilitySystemComponent);

	return EStateTreeRunStatus::Succeeded;
}

#if WITH_EDITOR
FText FAV_ApplyGameplayEffectStateTreeTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	
	if (!InstanceData)
	{
		return FText::FromString(TEXT("Apply Gameplay Effect"));
	}

	FString GameplayEffectClassName = TEXT("None");
	if (InstanceData->GameplayEffectClass)
	{
		GameplayEffectClassName = InstanceData->GameplayEffectClass->GetName();
	}

	return FText::FromString(FString::Printf(TEXT("Apply Gameplay Effect: %s at Level: %f"), *GameplayEffectClassName, InstanceData->GameplayEffectLevel));
}
#endif // WITH_EDITOR
