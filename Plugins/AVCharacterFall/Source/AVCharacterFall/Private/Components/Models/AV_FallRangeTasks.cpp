// Copyright Anton Vasserman, All Rights Reserved.

#include "Components/Models/AV_FallRangeTasks.h"

#include "Components/Models/AV_FallRangeState.h"
#include "Tasks/Falling/AV_FallingTaskBase.h"
#include "Tasks/Landed/AV_LandedTaskBase.h"

EAV_FallRangeState FAV_FallRangeTasks::TestRange(const FAV_FallRangeContext& ConditionContext)
{
	const bool bInRange = FallRange.TestRange(ConditionContext.FallHeight);
	
	if (ConditionContext.HitActor != nullptr)
	{
		if (State != EAV_FallRangeState::Exited && State != EAV_FallRangeState::Outside)
		{
			ExecuteFallingExitTasks(ConditionContext);
			ExecuteLandedTasks(ConditionContext);
		}
		
		State = EAV_FallRangeState::Outside;
		return State;
	}
	
	switch (State)
	{
	case EAV_FallRangeState::Outside:
		if (bInRange)
		{
			State = EAV_FallRangeState::Entered;
			ExecuteFallingEnterTasks(ConditionContext);
		}
		break;
	case EAV_FallRangeState::Entered:
		if (!bInRange)
		{
			State = EAV_FallRangeState::Exited;
			ExecuteFallingExitTasks(ConditionContext);
		}
		else
		{
			State = EAV_FallRangeState::Inside;
		}
		break;
	case EAV_FallRangeState::Inside:
		if (!bInRange)
		{
			State = EAV_FallRangeState::Exited;
			ExecuteFallingExitTasks(ConditionContext);
		}
		break;
	case EAV_FallRangeState::Exited:
		if (bInRange)
		{
			State = EAV_FallRangeState::Entered;
			ExecuteFallingEnterTasks(ConditionContext);
		}
		else
		{
			State = EAV_FallRangeState::Outside;
		}
		break;
	default:
		checkNoEntry();
	}

	return State;
}

void FAV_FallRangeTasks::ExecuteLandedTasks(const FAV_FallRangeContext& ConditionContext)
{
	FAV_LandedTaskContext TaskContext;
	TaskContext.Character = ConditionContext.Character;
	TaskContext.HitActor = ConditionContext.HitActor;
	TaskContext.FallHeight = ConditionContext.FallHeight;
	TaskContext.FallingComponent = ConditionContext.CharacterFallComponent;
			
	for (const UAV_LandedTaskBase* Task : LandedTasks)
	{
		Task->ExecuteTask(TaskContext);
	}
}

void FAV_FallRangeTasks::ExecuteFallingEnterTasks(const FAV_FallRangeContext& ConditionContext)
{
	FAV_FallingTaskContext TaskContext;
	TaskContext.Character = ConditionContext.Character;
	TaskContext.FallingComponent = ConditionContext.CharacterFallComponent;
	for (const UAV_FallingTaskBase* Task : FallingEnterTasks)
	{
		Task->ExecuteTask(TaskContext);
	}
}

void FAV_FallRangeTasks::ExecuteFallingExitTasks(const FAV_FallRangeContext& ConditionContext)
{
	FAV_FallingTaskContext TaskContext;
	TaskContext.Character = ConditionContext.Character;
	TaskContext.FallingComponent = ConditionContext.CharacterFallComponent;
	for (const UAV_FallingTaskBase* Task : FallingExitTasks)
	{
		Task->ExecuteTask(TaskContext);
	}
}
