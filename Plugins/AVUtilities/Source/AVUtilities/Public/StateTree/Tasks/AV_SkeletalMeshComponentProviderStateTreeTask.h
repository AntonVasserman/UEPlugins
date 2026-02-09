// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"

#include "AV_SkeletalMeshComponentProviderStateTreeTask.generated.h"

class APawn;
class USkeletalMeshComponent;

USTRUCT()
struct AVUTILITIES_API FAV_SkeletalMeshComponentProviderStateTreeTaskInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr<APawn> Pawn;
	
	UPROPERTY(EditAnywhere, Category = "Output")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
};

/**
 * This task is responsible for providing a skeletal mesh component to the state tree.
 * It's intended to be used as a Global State Tree Task.
 */
USTRUCT(Meta = (DisplayName = "Skeletal Mesh Component Provider"))
struct AVUTILITIES_API FAV_SkeletalMeshComponentProviderStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FAV_SkeletalMeshComponentProviderStateTreeTask();
	
	using FInstanceDataType = FAV_SkeletalMeshComponentProviderStateTreeTaskInstanceData;
	
	//~ FStateTreeTaskCommonBase
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	
#if WITH_EDITOR
	virtual FName GetIconName() const override { return FName("Node.Find"); }
	virtual FColor GetIconColor() const override { return UE::StateTree::Colors::Bronze; }
#endif // WITH_EDITOR
};
