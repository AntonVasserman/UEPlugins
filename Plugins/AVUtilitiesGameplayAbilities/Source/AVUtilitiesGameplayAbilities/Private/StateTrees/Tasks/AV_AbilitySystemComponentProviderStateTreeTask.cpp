// Copyright Anton Vasserman, All Rights Reserved.


#include "StateTrees/Tasks/AV_AbilitySystemComponentProviderStateTreeTask.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "StateTreeExecutionContext.h"
#include "GameFramework/Actor.h"

FAV_AbilitySystemComponentProviderStateTreeTask::FAV_AbilitySystemComponentProviderStateTreeTask()
{
	bShouldCallTick = false;
#if WITH_EDITORONLY_DATA
	bConsideredForCompletion = false;
	bCanEditConsideredForCompletion = false;
#endif
}

//~ FStateTreeTaskCommonBase

EStateTreeRunStatus FAV_AbilitySystemComponentProviderStateTreeTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	InstanceData.AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InstanceData.Actor);
	
	if (InstanceData.bCheckAbilitySystemComponent)
	{
		check(InstanceData.AbilitySystemComponent);
	}
	
	return InstanceData.AbilitySystemComponent ? EStateTreeRunStatus::Running : EStateTreeRunStatus::Failed;
}
