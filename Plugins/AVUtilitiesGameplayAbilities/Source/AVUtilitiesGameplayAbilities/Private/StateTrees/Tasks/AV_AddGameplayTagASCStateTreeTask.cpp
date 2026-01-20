// Copyright Anton Vasserman, All Rights Reserved.


#include "StateTrees/Tasks/AV_AddGameplayTagASCStateTreeTask.h"

#include "AbilitySystemComponent.h"
#include "StateTreeExecutionContext.h"

FAV_AddGameplayTagASCStateTreeTask::FAV_AddGameplayTagASCStateTreeTask()
{
	bShouldCallTick = false;
}

//~ FStateTreeTaskCommonBase

EStateTreeRunStatus FAV_AddGameplayTagASCStateTreeTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	// If ASC isn't set we won't throw, we will just not add the Tag
	if (InstanceData.AbilitySystemComponent == nullptr)
	{
		return EStateTreeRunStatus::Failed;
	}

	InstanceData.AbilitySystemComponent->AddLooseGameplayTag(InstanceData.GameplayTag, InstanceData.Count);
	
	return EStateTreeRunStatus::Succeeded;
}

void FAV_AddGameplayTagASCStateTreeTask::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	// If we can't find the Component we won't throw, we will just not add the Tag
	if (InstanceData.AbilitySystemComponent == nullptr)
	{
		return;
	}

	if (InstanceData.bRemoveOnExit)
	{
		InstanceData.AbilitySystemComponent->RemoveLooseGameplayTag(InstanceData.GameplayTag, InstanceData.Count);
	}
}

#if WITH_EDITOR
FText FAV_AddGameplayTagASCStateTreeTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	
	if (!InstanceData)
	{
		return FText::FromString(TEXT("Add Gameplay Tag"));
	}

	return FText::FromString(FString::Printf(TEXT("Add Gameplay Tag: %s to Ability System Component, with Count: %d"), *InstanceData->GameplayTag.GetTagName().ToString(), InstanceData->Count));
}
#endif // WITH_EDITOR
