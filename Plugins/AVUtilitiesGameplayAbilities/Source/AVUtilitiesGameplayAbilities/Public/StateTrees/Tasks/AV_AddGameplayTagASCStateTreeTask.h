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

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(EditAnywhere, Category = "Parameter")
	FGameplayTag GameplayTag;

	UPROPERTY(EditAnywhere, Category = "Parameter")
	int32 Count = 1;
	
	UPROPERTY(EditAnywhere, Category = "Parameter")
	bool bRemoveOnExit = false;
};

USTRUCT(Meta = (DisplayName = "Add Gameplay Tag (Ability System Component)", Category = "AVUtils|GameplayAbilities"))
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
	virtual FName GetIconName() const override { return FName("GameplayAbilitiesEditor|ClassIcon.AbilitySystemComponent"); }
#endif // WITH_EDITOR
};
