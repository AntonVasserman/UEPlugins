// Copyright Anton Vasserman, All Rights Reserved.

#include "StateTree/Tasks/AV_PlayForceFeedbackStateTreeTask.h"

#include "StateTreeExecutionContext.h"
#include "GameFramework/ForceFeedbackEffect.h"
#include "GameFramework/PlayerController.h"

FAV_PlayForceFeedbackStateTreeTask::FAV_PlayForceFeedbackStateTreeTask()
{
	bShouldCallTick = false;
}

//~ FStateTreeTaskCommonBase

EStateTreeRunStatus FAV_PlayForceFeedbackStateTreeTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	if (!IsValid(InstanceData.ForceFeedbackEffect))
	{
		return EStateTreeRunStatus::Failed;
	}

	FForceFeedbackParameters Params;
	Params.Tag = InstanceData.ForceFeedbackTag;
	Params.bLooping = InstanceData.bLoop;
	
	InstanceData.Controller->ClientPlayForceFeedback(InstanceData.ForceFeedbackEffect, Params);
	
	return EStateTreeRunStatus::Succeeded;
}

#if WITH_EDITOR
FText FAV_PlayForceFeedbackStateTreeTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	
	if (!InstanceData)
	{
		return FText::FromString(TEXT("Play Force Feedback"));
	}

	FString ForceFeedbackEffectName = TEXT("None");
	if (InstanceData->ForceFeedbackEffect)
	{
		ForceFeedbackEffectName = InstanceData->ForceFeedbackEffect->GetName();
	}

	return FText::FromString(FString::Printf(TEXT("Play Force Feedback: %s"), *ForceFeedbackEffectName));
}
#endif // WITH_EDITOR
