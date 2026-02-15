// Copyright Anton Vasserman, All Rights Reserved.

#include "StateTrees/Conditions/AV_HasMatchingTagASCStateTreeCondition.h"

#include "AbilitySystemComponent.h"
#include "StateTreeExecutionContext.h"

//~ FStateTreeConditionCommonBase

bool FAV_HasMatchingTagASCStateTreeCondition::TestCondition(FStateTreeExecutionContext& Context) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	return InstanceData.AbilitySystemComponent->HasMatchingGameplayTag(InstanceData.Tag) ? !InstanceData.bInvert : InstanceData.bInvert;
}

#if WITH_EDITOR
FText FAV_HasMatchingTagASCStateTreeCondition::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	check(InstanceData);

	return FText::FromString(FString::Printf(TEXT("ASC has%s Matching Tag: %s"), InstanceData->bInvert ? TEXT(" not") : TEXT(""), *InstanceData->Tag.ToString()));
}
#endif // WITH_EDITOR
