// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "AV_VolumeFilter.generated.h"

class AActor;
class UPrimitiveComponent;

UCLASS(Abstract)
class AVUTILITIES_API UAV_VolumeFilter : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
	bool Filter(AActor* OtherActor, UPrimitiveComponent* OtherComp) const;
	virtual bool Filter_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp) const { /* By default do nothing, this should be implemented by derived classes */ return true; }
};
