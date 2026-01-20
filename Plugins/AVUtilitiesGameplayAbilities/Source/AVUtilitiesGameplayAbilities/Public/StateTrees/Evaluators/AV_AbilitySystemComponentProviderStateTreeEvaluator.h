// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "AbilitySystemComponent.h"
#include "StateTreeEvaluatorBase.h"

#include "AV_AbilitySystemComponentProviderStateTreeEvaluator.generated.h"

class UAbilitySystemComponent;

USTRUCT()
struct AVUTILITIESGAMEPLAYABILITIES_API FAV_AbilitySystemComponentProviderStateTreeEvaluatorInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr<AActor> Actor;
	
	UPROPERTY(EditAnywhere, Category = "Outputs")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	bool bCheckAbilitySystemComponent = false;
};

USTRUCT(Meta = (DisplayName = "Ability System Component Provider"))
struct AVUTILITIESGAMEPLAYABILITIES_API FAV_AbilitySystemComponentProviderStateTreeEvaluator : public FStateTreeEvaluatorCommonBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FAV_AbilitySystemComponentProviderStateTreeEvaluatorInstanceData;
	
	//~ FStateTreeEvaluatorCommonBase
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual void TreeStart(FStateTreeExecutionContext& Context) const override;
};
