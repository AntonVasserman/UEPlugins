// Copyright Anton Vasserman, All Rights Reserved.


#include "Components/AV_FallRange.h"

#include "AVMacros.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

bool FAV_FallRange::TestRange(const FAV_FallRangeContext& ConditionContext) const
{
	switch (ThresholdType)
	{
	case EAV_FallRangeThresholdType::LessThan:
		return ConditionContext.FallHeight < FallHeightThreshold;
	case EAV_FallRangeThresholdType::InRange:
		return ConditionContext.FallHeight >= FallHeightThresholdMin && ConditionContext.FallHeight <= FallHeightThresholdMax;
	case EAV_FallRangeThresholdType::GreaterThan:
		return ConditionContext.FallHeight > FallHeightThreshold;
	AV_DEFAULT_CHECKNOENTRY
	}

	return false;
}
