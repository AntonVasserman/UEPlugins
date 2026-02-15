// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"

#include "AV_CancelGameplayAbilitiesByTagStateTreeTask.generated.h"

class UAbilitySystemComponent;
struct FGameplayTagContainer;
class AAIController;

USTRUCT()
struct FAV_CancelGameplayAbilitiesByTagStateTreeTaskInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category = "Parameter")
	FGameplayTagContainer CancelAbilityWithTags = FGameplayTagContainer::EmptyContainer;

	UPROPERTY(EditAnywhere, Category = "Parameter")
	FGameplayTagContainer CancelAbilityWithoutTags = FGameplayTagContainer::EmptyContainer;
};

USTRUCT(Meta = (DisplayName = "Cancel Gameplay Abilities (by Tag)", Category = "AVUtils|GameplayAbilities"))
struct AVUTILITIESGAMEPLAYABILITIES_API FAV_CancelGameplayAbilitiesByTagStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FAV_CancelGameplayAbilitiesByTagStateTreeTaskInstanceData;
	
	//~ FStateTreeTaskCommonBase
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	
#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
	virtual FName GetIconName() const override { return FName("GameplayAbilitiesEditor|ClassIcon.AbilitySystemComponent"); }
#endif
};
