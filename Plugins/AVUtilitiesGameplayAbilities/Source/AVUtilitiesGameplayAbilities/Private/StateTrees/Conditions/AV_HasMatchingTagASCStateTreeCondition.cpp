// Copyright Anton Vasserman, All Rights Reserved.

#include "StateTrees/Conditions/AV_HasMatchingTagASCStateTreeCondition.h"

#include "AbilitySystemComponent.h"
#include "StateTreeExecutionContext.h"

bool FAV_HasMatchingTagASCStateTreeCondition::TestCondition(FStateTreeExecutionContext& Context) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	return InstanceData.AbilitySystemComponent->HasMatchingGameplayTag(InstanceData.Tag) ? !InstanceData.bInvert : InstanceData.bInvert;
}
