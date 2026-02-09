// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"

#include "AV_SpawnSoundAtLocationStateTreeTask.generated.h"

class USoundAttenuation;
class USoundConcurrency;
class USoundBase;

USTRUCT()
struct FAV_SpawnSoundAtLocationStateTreeTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Parameters")
	TSoftObjectPtr<USoundBase> Sound;
	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	FVector Location = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	FRotator Rotation = FRotator::ZeroRotator;
	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	float VolumeMultiplier = 1.f;
	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	float PitchMultiplier = 1.f;
	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	float StartTime = 0.f;
	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	TSoftObjectPtr<USoundAttenuation> AttenuationSettings;
	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	TSoftObjectPtr<USoundConcurrency> ConcurrencySettings;
	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	bool bAutoDestroy = true;
};

USTRUCT(Meta = (DisplayName = "Spawn Sound At Location"))
struct AVUTILITIES_API FAV_SpawnSoundAtLocationStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FAV_SpawnSoundAtLocationStateTreeTask();
	
	using FInstanceDataType = FAV_SpawnSoundAtLocationStateTreeTaskInstanceData;
	
	//~ FStateTreeTaskCommonBase
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
#endif // WITH_EDITOR
};
