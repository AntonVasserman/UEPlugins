// Copyright Anton Vasserman, All Rights Reserved.

#include "StateTrees/Evaluators/AV_AbilitySystemComponentProviderStateTreeEvaluator.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "StateTreeExecutionContext.h"

//~ FStateTreeEvaluatorCommonBase

void FAV_AbilitySystemComponentProviderStateTreeEvaluator::TreeStart(FStateTreeExecutionContext& Context) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	InstanceData.AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InstanceData.Actor);
	
	if (InstanceData.bCheckAbilitySystemComponent)
	{
		check(InstanceData.AbilitySystemComponent);
	}
}
