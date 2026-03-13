// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "AV_MathLibrary.generated.h"

UCLASS(MinimalAPI)
class UAV_MathLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintPure, Category = "Math|Float")
	static AVUTILITIES_API float NegateFloat(const float InValue) { return -InValue; }
	
	UFUNCTION(BlueprintPure, Category = "Math|Double")
	static AVUTILITIES_API double NegateDouble(const double InValue) { return -InValue; }
};
