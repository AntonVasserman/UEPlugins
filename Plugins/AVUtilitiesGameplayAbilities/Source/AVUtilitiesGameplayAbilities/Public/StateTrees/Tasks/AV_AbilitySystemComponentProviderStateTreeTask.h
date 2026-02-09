// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"

#include "AV_AbilitySystemComponentProviderStateTreeTask.generated.h"

class AActor;
class UAbilitySystemComponent;

USTRUCT()
struct AVUTILITIESGAMEPLAYABILITIES_API FAV_AbilitySystemComponentProviderStateTreeTaskInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr<AActor> Actor;
	
	UPROPERTY(EditAnywhere, Category = "Outputs")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	bool bCheckAbilitySystemComponent = false;
};

/**
 * This task is responsible for providing an ability system component to the state tree.
 * It's intended to be used as a Global State Tree Task.
 */
USTRUCT(Meta = (DisplayName = "Ability System Component Provider"))
struct AVUTILITIESGAMEPLAYABILITIES_API FAV_AbilitySystemComponentProviderStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FAV_AbilitySystemComponentProviderStateTreeTask();
	
	using FInstanceDataType = FAV_AbilitySystemComponentProviderStateTreeTaskInstanceData;
	
	//~ FStateTreeTaskCommonBase
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	
#if WITH_EDITOR
	virtual FName GetIconName() const override { return FName("Node.Find"); }
	virtual FColor GetIconColor() const override { return UE::StateTree::Colors::Bronze; }
#endif // WITH_EDITOR
};
