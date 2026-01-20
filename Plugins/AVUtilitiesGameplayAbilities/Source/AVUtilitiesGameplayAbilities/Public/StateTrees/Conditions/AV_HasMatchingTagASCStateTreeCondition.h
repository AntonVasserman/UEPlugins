// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "StateTreeConditionBase.h"

#include "AV_HasMatchingTagASCStateTreeCondition.generated.h"

class UAbilitySystemComponent;
struct FGameplayTag;

USTRUCT()
struct AVUTILITIESGAMEPLAYABILITIES_API FAV_HasMatchingTagASCStateTreeConditionInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category = "Parameters")
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, Category = "Parameters")
	bool bInvert = false;
};

USTRUCT(DisplayName = "Has Matching Tag (Ability System Component)")
struct AVUTILITIESGAMEPLAYABILITIES_API FAV_HasMatchingTagASCStateTreeCondition : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FAV_HasMatchingTagASCStateTreeConditionInstanceData;

	//~ FStateTreeConditionCommonBase
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
};
