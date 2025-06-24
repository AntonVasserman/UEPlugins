// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EAV_FallRangeThresholdType : uint8
{
	LessThan			UMETA(DisplayName = "Less Than", Description = "Fall Height must be less than the specified value"),
	InRange				UMETA(DisplayName = "In Range", Description = "Fall Height must be in the specified range"),
	GreaterThan			UMETA(DisplayName = "Greater Than", Description = "Fall Height must be greater than the specified value"),
};