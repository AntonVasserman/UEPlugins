// Copyright Anton Vasserman, All Rights Reserved.


#include "StateTree/Conditions/AV_GameplayTagEqualsStateTreeCondition.h"

#include "StateTreeExecutionContext.h"

bool FAV_GameplayTagEqualsStateTreeCondition::TestCondition(FStateTreeExecutionContext& Context) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	return InstanceData.Left == InstanceData.Right ^ InstanceData.bInvert;
}

#if WITH_EDITOR
FText FAV_GameplayTagEqualsStateTreeCondition::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	check(InstanceData);
	
	FText LeftValue = BindingLookup.GetBindingSourceDisplayName(FPropertyBindingPath(ID, GET_MEMBER_NAME_CHECKED(FInstanceDataType, Left)), Formatting);
	if (LeftValue.IsEmpty())
	{
		LeftValue = FText::FromString(TEXT("Gameplay Tag"));
	}

	FText RightValue = BindingLookup.GetBindingSourceDisplayName(FPropertyBindingPath(ID, GET_MEMBER_NAME_CHECKED(FInstanceDataType, Right)), Formatting);
	if (RightValue.IsEmpty())
	{
		RightValue = FText::FromString(FString::Printf(TEXT("%s"), *InstanceData->Right.ToString()));
	}

	return FText::FromString(FString::Printf(TEXT("%s%s equals to %s"), *LeftValue.ToString(), InstanceData->bInvert ? TEXT(" not") : TEXT(""), *RightValue.ToString()));
}
#endif // WITH_EDITOR
