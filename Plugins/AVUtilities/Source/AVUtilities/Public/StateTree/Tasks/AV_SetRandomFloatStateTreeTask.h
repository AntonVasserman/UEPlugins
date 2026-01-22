// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"

#include "AV_SetRandomFloatStateTreeTask.generated.h"

USTRUCT()
struct FAV_SetRandomFloatStateTreeTaskInstanceData
{
	GENERATED_BODY()

	/** Minimum random value */
	UPROPERTY(EditAnywhere, Category = "Parameter")
	float MinValue = 0.0f;

	/** Maximum random value */
	UPROPERTY(EditAnywhere, Category = "Parameter")
	float MaxValue = 0.0f;

	/** Output calculated value */
	UPROPERTY(EditAnywhere, Category = "Output")
	float OutValue = 0.0f;
};

/**
 *  StateTree task to calculate a random float value within the specified range
 */
USTRUCT(Meta = (DisplayName = "Set Random Float", Category = "Shooter"))
struct FAV_SetRandomFloatStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FAV_SetRandomFloatStateTreeTaskInstanceData;

	//~ FStateTreeTaskCommonBase
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
#endif // WITH_EDITOR
};