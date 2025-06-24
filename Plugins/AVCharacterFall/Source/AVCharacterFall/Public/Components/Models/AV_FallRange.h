// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AV_FallRangeThresholdType.h"
#include "AV_FallRange.generated.h"

USTRUCT()
struct AVCHARACTERFALL_API FAV_FallRange
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "")
	EAV_FallRangeThresholdType ThresholdType = EAV_FallRangeThresholdType::LessThan;
	
	UPROPERTY(EditDefaultsOnly, Category = "", Meta = (EditCondition = "ThresholdType != EAV_FallRangeThresholdType::InRange", EditConditionHides))
	float FallHeightThreshold = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "", Meta = (EditCondition = "ThresholdType == EAV_FallRangeThresholdType::InRange", EditConditionHides))
	float FallHeightThresholdMin = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "", Meta = (EditCondition = "ThresholdType == EAV_FallRangeThresholdType::InRange", EditConditionHides))
	float FallHeightThresholdMax = 0.f;

	bool TestRange(float FallHeight) const;
};
