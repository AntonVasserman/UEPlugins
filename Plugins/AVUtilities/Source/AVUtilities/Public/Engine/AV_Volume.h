// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "AV_Volume.generated.h"

class UAV_VolumeAction;
class UAV_VolumeFilter;
class UBoxComponent;

UCLASS(Abstract)
class AVUTILITIES_API AAV_Volume : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY()
	TObjectPtr<UBoxComponent> BoxComponent;
	
#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TObjectPtr<UBillboardComponent> BillboardComponent;
#endif // WITH_EDITORONLY_DATA
	
public:
	AAV_Volume();
	
	UFUNCTION(BlueprintCallable, Category = "Volume")
	bool IsInVolume(const FVector& WorldLocation) const;
	
	UFUNCTION(BlueprintCallable, Category = "Volume")
	float GetClosestPointOnVolume(const FVector& WorldLocation, FVector& OutClosestPointOnVolume) const;
	
private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Config|Volume", Meta = (AllowPrivateAccess = "true"))
	FVector VolumeExtent = FVector(50.f);
	
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditDefaultsOnly, Category = "Config|Billboard", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> Sprite = nullptr;
#endif // WITH_EDITORONLY_DATA
	
	UPROPERTY(EditDefaultsOnly, Category = "Config|Volume", Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAV_VolumeFilter>> VolumeFilters;
	
	UPROPERTY(EditDefaultsOnly, Category = "Config|Volume", Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAV_VolumeAction>> VolumeActions;
	
	UFUNCTION()
	void BoxComponent_OnComponentBeginOverlap(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
	UFUNCTION()
	void BoxComponent_OnComponentEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp, 
		int OtherBodyIndex);
	
	//~ AActor
public:
	virtual void OnConstruction(const FTransform& Transform) override;
protected:
	virtual void BeginPlay() override;
};
