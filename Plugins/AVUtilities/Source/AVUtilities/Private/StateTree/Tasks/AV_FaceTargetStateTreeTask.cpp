// Copyright Anton Vasserman, All Rights Reserved.


#include "StateTree/Tasks/AV_FaceTargetStateTreeTask.h"

#include "AIController.h"
#include "StateTreeExecutionContext.h"

//~ FStateTreeTaskCommonBase
EStateTreeRunStatus FAV_FaceTargetStateTreeTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	if (Transition.ChangeType == EStateTreeStateChangeType::Changed)
	{
		const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

		if (InstanceData.bTargetIsActor)
		{
			InstanceData.Controller->SetFocus(InstanceData.TargetActorToFace);	
		}
		else
		{
			InstanceData.Controller->SetFocalPoint(InstanceData.TargetLocationToFace);
		}
	}

	return EStateTreeRunStatus::Running;
}

void FAV_FaceTargetStateTreeTask::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	if (Transition.ChangeType == EStateTreeStateChangeType::Changed)
	{
		const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
		
		InstanceData.Controller->ClearFocus(EAIFocusPriority::Gameplay);
	}
}

#if WITH_EDITOR
FText FAV_FaceTargetStateTreeTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();

	const FString TargetString = InstanceData->bTargetIsActor ? TEXT("Actor") : TEXT("Location");
	FString TargetName = TEXT("None");
	if (InstanceData->bTargetIsActor && InstanceData->TargetActorToFace)
	{
		TargetName = InstanceData->TargetActorToFace->GetName();
	}
	else if (InstanceData->bTargetIsActor == false)
	{
		TargetName = InstanceData->TargetLocationToFace.ToString();
	}
	
	return FText::FromString(FString::Printf(TEXT("Face Target %s: %s"), *TargetString, *TargetName));
}
#endif // WITH_EDITOR