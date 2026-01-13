// Copyright Anton Vasserman, All Rights Reserved.

#include "StateTree/Conditions/AV_ObjectImplementsInterfaceStateTreeCondition.h"

#include "StateTreeExecutionContext.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/Interface.h"

//~ FStateTreeConditionCommonBase

bool FAV_ObjectImplementsInterfaceStateTreeCondition::TestCondition(FStateTreeExecutionContext& Context) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	if (!InstanceData.Interface)
	{
		return false;
	}

	const bool bImplementsInterface = UKismetSystemLibrary::DoesImplementInterface(InstanceData.Object, InstanceData.Interface);
	return bImplementsInterface ^ InstanceData.bInvert;
}

#if WITH_EDITOR
FText FAV_ObjectImplementsInterfaceStateTreeCondition::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	
	if (!InstanceData)
	{
		return FText::FromString(TEXT("Object Implements Interface"));
	}

	FString InterfaceName = TEXT("None");
	if (InstanceData->Interface)
	{
		InterfaceName = InstanceData->Interface->GetName();
	}

	return FText::FromString(FString::Printf(TEXT("Object%s Implements %s"), InstanceData->bInvert ? TEXT(" not") : TEXT(""), *InterfaceName));
}
#endif // WITH_EDITOR
