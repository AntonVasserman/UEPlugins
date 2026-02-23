// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AV_VolumeActionBase.generated.h"

class AActor;
class AAV_Volume;
class UPrimitiveComponent;

USTRUCT(BlueprintType)
struct AVUTILITIES_API FAV_VolumeActionContext
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category = "")
	TWeakObjectPtr<AAV_Volume> OverlappedVolume;
	
	UPROPERTY(BlueprintReadOnly, Category = "")
	TWeakObjectPtr<UPrimitiveComponent> OverlappedComponent;
	
	UPROPERTY(BlueprintReadOnly, Category = "")
	TWeakObjectPtr<AActor> OtherActor;
	
	UPROPERTY(BlueprintReadOnly, Category = "")
	TWeakObjectPtr<UPrimitiveComponent> OtherComp;
};

UCLASS(Abstract, Blueprintable, EditInlineNew)
class AVUTILITIES_API UAV_VolumeActionBase : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void Execute(const FAV_VolumeActionContext& Context) const;
	virtual void Execute_Implementation(const FAV_VolumeActionContext& Context) const { /* By default do nothing, this should be implemented by derived classes */ }
};
