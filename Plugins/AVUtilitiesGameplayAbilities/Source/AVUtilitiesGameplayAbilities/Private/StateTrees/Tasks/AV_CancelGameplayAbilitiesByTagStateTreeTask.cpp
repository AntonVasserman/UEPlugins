// Copyright Anton Vasserman, All Rights Reserved.


#include "StateTrees/Tasks/AV_CancelGameplayAbilitiesByTagStateTreeTask.h"

#include "AbilitySystemComponent.h"
#include "StateTreeExecutionContext.h"


//~ FStateTreeTaskCommonBase

EStateTreeRunStatus FAV_CancelGameplayAbilitiesByTagStateTreeTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	if (!InstanceData.AbilitySystemComponent)
	{
		return EStateTreeRunStatus::Failed;
	}
	
	const FGameplayTagContainer CancelAbilitiesWithTags = InstanceData.CancelAbilityWithTags;
	const FGameplayTagContainer CancelAbilitiesWithoutTags = InstanceData.CancelAbilityWithoutTags;
	
	InstanceData.AbilitySystemComponent->CancelAbilities(
		CancelAbilitiesWithTags.IsValid() ? &CancelAbilitiesWithTags : nullptr, 
		CancelAbilitiesWithoutTags.IsValid() ? &CancelAbilitiesWithoutTags : nullptr);

	return EStateTreeRunStatus::Succeeded;
}

#if WITH_EDITOR
FText FAV_CancelGameplayAbilitiesByTagStateTreeTask::GetDescription(const FGuid& ID, const FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, const EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	
	if (!InstanceData)
	{
		return FText::FromString(TEXT("Cancel Gameplay Abilities (by Tags)"));
	}

	return FText::FromString(FString::Printf(TEXT("Cancel Gameplay Abilities with Tags: %s, and without Tags: %s"), *InstanceData->CancelAbilityWithTags.ToStringSimple(), *InstanceData->CancelAbilityWithoutTags.ToStringSimple()));
}
#endif