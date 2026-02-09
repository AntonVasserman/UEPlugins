// Copyright Anton Vasserman, All Rights Reserved.


#include "StateTree/Tasks/AV_SkeletalMeshComponentProviderStateTreeTask.h"

#include "StateTreeExecutionContext.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Pawn.h"

//~ FStateTreeTaskCommonBase

FAV_SkeletalMeshComponentProviderStateTreeTask::FAV_SkeletalMeshComponentProviderStateTreeTask()
{
	bShouldCallTick = false;
#if WITH_EDITORONLY_DATA
	bConsideredForCompletion = false;
	bCanEditConsideredForCompletion = false;
#endif
}

EStateTreeRunStatus FAV_SkeletalMeshComponentProviderStateTreeTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	InstanceData.SkeletalMeshComponent = InstanceData.Pawn->FindComponentByClass<USkeletalMeshComponent>();
	
	return IsValid(InstanceData.SkeletalMeshComponent) ? EStateTreeRunStatus::Running : EStateTreeRunStatus::Failed;
}
