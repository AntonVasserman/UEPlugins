// Copyright Anton Vasserman, All Rights Reserved.


#include "Components/AV_FallRange.h"

#include "AVMacros.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

EAV_FallRangeState FAV_FallRange::TestRange(const FAV_FallRangeContext& ConditionContext)
{
	bool bInRange = false;

	if (ConditionContext.Character->GetMovementComponent()->IsFalling())
	{
		switch (ThresholdType)
		{
		case EAV_FallRangeThresholdType::LessThan:
			bInRange = ConditionContext.FallHeight < FallHeightThreshold;
			break;
		case EAV_FallRangeThresholdType::InRange:
			bInRange = ConditionContext.FallHeight >= FallHeightThresholdMin && ConditionContext.FallHeight <= FallHeightThresholdMax;
			break;
		case EAV_FallRangeThresholdType::GreaterThan:
			bInRange = ConditionContext.FallHeight > FallHeightThreshold;
			break;
		AV_DEFAULT_CHECKNOENTRY
		}
	}

	switch (State)
	{
	case EAV_FallRangeState::Outside:
		if (bInRange)
		{
			State = EAV_FallRangeState::Entered;
		}
		break;
	case EAV_FallRangeState::Entered:
		State = bInRange ? EAV_FallRangeState::Inside : EAV_FallRangeState::Exited;
		break;
	case EAV_FallRangeState::Inside:
		if (!bInRange)
		{
			State = EAV_FallRangeState::Exited;
		}
		break;
	case EAV_FallRangeState::Exited:
		State = bInRange ? EAV_FallRangeState::Entered : EAV_FallRangeState::Outside;
		break;
	AV_DEFAULT_CHECKNOENTRY
	}

	return State;
}
