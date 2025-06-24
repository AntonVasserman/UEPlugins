// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EAV_FallRangeState : uint8
{
	Outside		UMETA(DisplayName = "Outside", ToolTip = "Outside of the fall range"),
	Entered		UMETA(DisplayName = "Enter", ToolTip = "Entered the fall range"),
	Inside		UMETA(DisplayName = "Inside", ToolTip = "Inside of the fall range"),
	Exited		UMETA(DisplayName = "Exited", ToolTip = "Exited the fall range")
};
