// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "StateTreeTaskBase.h"

#include "AV_AddGameplayTagASCStateTreeTask.generated.h"

class UAbilitySystemComponent;
struct FGameplayTag;

USTRUCT()
struct AVUTILITIESGAMEPLAYABILITIES_API FAV_AddGameplayTagASCStateTreeTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	FGameplayTag GameplayTag;

	UPROPERTY(EditAnywhere, Category = "Parameters")
	int32 Count = 1;
	
	UPROPERTY(EditAnywhere, Category = "Parameters")
	bool bRemoveOnExit = false;
};

USTRUCT(Meta = (DisplayName = "Add Gameplay Tag (Ability System Component)"))
struct AVUTILITIESGAMEPLAYABILITIES_API FAV_AddGameplayTagASCStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()
	
	FAV_AddGameplayTagASCStateTreeTask();
	
	using FInstanceDataType = FAV_AddGameplayTagASCStateTreeTaskInstanceData;

	//~ FStateTreeTaskCommonBase
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	
#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
#endif // WITH_EDITOR
};
