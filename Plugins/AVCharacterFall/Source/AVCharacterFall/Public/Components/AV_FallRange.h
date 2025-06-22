// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AV_FallRange.generated.h"

UENUM(Blueprintable)
enum class EAV_FallRangeThresholdType : uint8
{
	LessThan			UMETA(DisplayName = "Less Than", Description = "Fall Height must be less than the specified value"),
	InRange				UMETA(DisplayName = "In Range", Description = "Fall Height must be in the specified range"),
	GreaterThan			UMETA(DisplayName = "Greater Than", Description = "Fall Height must be greater than the specified value"),
};

UENUM(BlueprintType)
enum class EAV_FallRangeState : uint8
{
	Outside		UMETA(DisplayName = "Outside", ToolTip = "Outside of the fall range"),
	Inside		UMETA(DisplayName = "Inside", ToolTip = "Inside of the fall range"),
};

USTRUCT(BlueprintType)
struct AVCHARACTERFALL_API FAV_FallRangeContext
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACharacter> Character;

	UPROPERTY(BlueprintReadOnly)
	float FallHeight = 0.f;
};

USTRUCT(Blueprintable, Meta = (DisplayName = "Fall Range"))
struct AVCHARACTERFALL_API FAV_FallRange
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "", Meta = (AllowPrivateAccess = "true"))
	EAV_FallRangeThresholdType ThresholdType = EAV_FallRangeThresholdType::LessThan;
	
	UPROPERTY(EditDefaultsOnly, Category = "", Meta = (AllowPrivateAccess = "true", EditCondition = "ThresholdType != EAV_FallRangeThresholdType::InRange", EditConditionHides))
	float FallHeightThreshold;

	UPROPERTY(EditDefaultsOnly, Category = "", Meta = (AllowPrivateAccess = "true", EditCondition = "ThresholdType == EAV_FallRangeThresholdType::InRange", EditConditionHides))
	float FallHeightThresholdMin;

	UPROPERTY(EditDefaultsOnly, Category = "", Meta = (AllowPrivateAccess = "true", EditCondition = "ThresholdType == EAV_FallRangeThresholdType::InRange", EditConditionHides))
	float FallHeightThresholdMax;

	bool TestRange(const FAV_FallRangeContext& ConditionContext) const;
};
