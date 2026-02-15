// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "StateTreeTaskBase.h"

#include "AV_ActivateGameplayAbilitiesByTagStateTreeTask.generated.h"

struct FAbilityEndedData;
class UAbilitySystemComponent;
class UGameplayAbility;

USTRUCT()
struct FAV_ActivateGameplayAbilitiesByTagStateTreeTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(EditAnywhere, Category = "Output")
	FGameplayAbilitySpecHandle AbilitySpecHandle = FGameplayAbilitySpecHandle();
	
	UPROPERTY(EditAnywhere, Category = "Output")
	bool bAbilityHasEnded = false;
	
	UPROPERTY(EditAnywhere, Category = "Output")
	bool bAbilityWasCancelled = false;
	
	UPROPERTY(EditAnywhere, Category = "Parameter")
	FGameplayTagContainer AbilityActivationTags = FGameplayTagContainer::EmptyContainer;
	
	TWeakObjectPtr<UGameplayAbility> AbilityThatEnded;
	FDelegateHandle AbilityEndedDelegateHandle;
	
	bool CheckAbilityThatHasEnded(const FAbilityEndedData& AbilityEndedData) const;
};

USTRUCT(Meta = (DisplayName = "Activate Gameplay Abilities (by Tag)", Category = "AVUtils|GameplayAbilities"))
struct AVUTILITIESGAMEPLAYABILITIES_API FAV_ActivateGameplayAbilitiesByTagStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FAV_ActivateGameplayAbilitiesByTagStateTreeTaskInstanceData;

private:
	UPROPERTY(EditAnywhere, Category = "Parameter")
	bool bShouldFinishStateWhenAbilityCompletes = true;
	
	UPROPERTY(EditAnywhere, Category = "Parameter")
	bool bTreatCancelledAbilityAsSuccess = false;
	
	UPROPERTY(EditAnywhere, Category = "Parameter")
	bool bShouldCancelAbilityWhenStateFinishes = false;
	
	//~ FStateTreeTaskCommonBase
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
	virtual FName GetIconName() const override { return FName("GameplayAbilitiesEditor|ClassIcon.AbilitySystemComponent"); }
#endif
};
