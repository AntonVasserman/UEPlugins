// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"

#include "AV_FaceTargetStateTreeTask.generated.h"

class AAIController;

USTRUCT()
struct AVUTILITIES_API FAV_FaceTargetStateTreeTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr<AAIController> Controller;

	UPROPERTY(EditAnywhere, Category = "Parameter")
	bool bTargetIsActor = true;
	
	UPROPERTY(EditAnywhere, Category = "Input", Meta = (EditCondition = "bTargetIsActor == true"))
	TObjectPtr<AActor> TargetActorToFace = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Parameter", Meta = (EditCondition = "bTargetIsActor == false"))
	FVector TargetLocationToFace = FVector::ZeroVector;
};

/**
 *  StateTree task to face an AI-Controlled Pawn towards a target (can be an Actor or a Location)
 */
USTRUCT(Meta = (DisplayName = "Face Target"))
struct AVUTILITIES_API FAV_FaceTargetStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FAV_FaceTargetStateTreeTaskInstanceData;

	//~ FStateTreeTaskCommonBase
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
#endif // WITH_EDITOR
};
