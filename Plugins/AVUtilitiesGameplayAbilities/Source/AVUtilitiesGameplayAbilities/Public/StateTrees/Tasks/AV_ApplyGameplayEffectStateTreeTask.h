// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "GameplayEffect.h"
#include "StateTreeTaskBase.h"
#include "Templates/SubclassOf.h"

#include "AV_ApplyGameplayEffectStateTreeTask.generated.h"

class UAbilitySystemComponent;

USTRUCT()
struct AVUTILITIESGAMEPLAYABILITIES_API FAV_ApplyGameplayEffectStateTreeTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	TSubclassOf<UGameplayEffect> GameplayEffectClass = nullptr;

	UPROPERTY(EditAnywhere, Category = "Parameters", Meta = (EditCondition = "GameplayEffectClass != nullptr", EditConditionHides))
	float GameplayEffectLevel = 1.f;
};

USTRUCT(Meta = (DisplayName = "Apply Gameplay Effect"))
struct AVUTILITIESGAMEPLAYABILITIES_API FAV_ApplyGameplayEffectStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FAV_ApplyGameplayEffectStateTreeTask();

	using FInstanceDataType = FAV_ApplyGameplayEffectStateTreeTaskInstanceData;

	//~ FStateTreeTaskCommonBase
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
#endif // WITH_EDITOR
};
