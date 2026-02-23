// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "AV_VolumeFilterBase.generated.h"

class AActor;
class UPrimitiveComponent;

UCLASS(Abstract, Blueprintable, EditInlineNew)
class AVUTILITIES_API UAV_VolumeFilterBase : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
	bool Filter(AActor* OtherActor, UPrimitiveComponent* OtherComp) const;
	virtual bool Filter_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp) const { /* By default do nothing, this should be implemented by derived classes */ return true; }
};
