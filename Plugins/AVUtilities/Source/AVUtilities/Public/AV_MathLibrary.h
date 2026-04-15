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
	
	/**
	 * Calculates and returns the direction vector from point A to point B.
	 * The direction vector is normalized to have a length of 1.
	 *
	 * @param A The starting point of the vector.
	 * @param B The ending point of the vector.
	 * @return A normalized direction vector from A to B.
	 */
	UFUNCTION(BlueprintPure, Category = "Math|Vector")
	static AVUTILITIES_API FVector GetDirectionVector(const FVector& A, const FVector& B) { return (B - A).GetSafeNormal(); }

	/**
	 * Calculates and returns the displacement vector from point A to point B.
	 * The displacement vector represents the difference between the two points, including both direction and distance.
	 *
	 * @param A The starting point of the vector.
	 * @param B The ending point of the vector.
	 * @return The displacement vector from A to B.
	 */
	UFUNCTION(BlueprintPure, Category = "Math|Vector")
	static AVUTILITIES_API FVector GetDisplacementVector(const FVector& A, const FVector& B) { return B - A; }
};
