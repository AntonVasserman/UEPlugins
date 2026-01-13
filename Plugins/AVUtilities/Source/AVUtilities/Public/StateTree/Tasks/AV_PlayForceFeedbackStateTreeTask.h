// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "UObject/Object.h"
#include "AV_PlayForceFeedbackStateTreeTask.generated.h"

class APlayerController;
class UForceFeedbackEffect;

USTRUCT()
struct AVUTILITIES_API FAV_PlayForceFeedbackStateTreeTaskInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr<APlayerController> Controller = nullptr;

	UPROPERTY(EditAnywhere, Category = "Parameters")
	TObjectPtr<UForceFeedbackEffect> ForceFeedbackEffect = nullptr;

	UPROPERTY(EditAnywhere, Category = "Parameters")
	FName ForceFeedbackTag = NAME_None;

	UPROPERTY(EditAnywhere, Category = "Parameters")
	bool bLoop = false;
};

USTRUCT(Meta = (DisplayName = "Play Force Feedback"))
struct AVUTILITIES_API FAV_PlayForceFeedbackStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FAV_PlayForceFeedbackStateTreeTask();
	
	using FInstanceDataType = FAV_PlayForceFeedbackStateTreeTaskInstanceData;

	//~ FStateTreeTaskCommonBase
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
#endif // WITH_EDITOR
};
