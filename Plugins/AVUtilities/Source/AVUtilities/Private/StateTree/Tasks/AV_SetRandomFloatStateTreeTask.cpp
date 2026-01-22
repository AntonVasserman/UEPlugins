// Copyright Anton Vasserman, All Rights Reserved.


#include "StateTree/Tasks/AV_SetRandomFloatStateTreeTask.h"

#include "StateTreeExecutionContext.h"

//~ FStateTreeTaskCommonBase

EStateTreeRunStatus FAV_SetRandomFloatStateTreeTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	if (Transition.ChangeType == EStateTreeStateChangeType::Changed)
	{
		FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

		InstanceData.OutValue = FMath::RandRange(InstanceData.MinValue, InstanceData.MaxValue);
	}

	return EStateTreeRunStatus::Running;
}

#if WITH_EDITOR
FText FAV_SetRandomFloatStateTreeTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting /*= EStateTreeNodeFormatting::Text*/) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	
	return FText::FromString(FString::Printf(TEXT("Set Random Float between [%f, %f]"), InstanceData->MinValue, InstanceData->MaxValue));
}
#endif // WITH_EDITOR
