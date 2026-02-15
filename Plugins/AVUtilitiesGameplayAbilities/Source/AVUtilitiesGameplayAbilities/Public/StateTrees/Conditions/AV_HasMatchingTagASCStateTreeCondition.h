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

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category = "Parameter")
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, Category = "Parameter")
	bool bInvert = false;
};

USTRUCT(Meta = (DisplayName = "Has Matching Tag (Ability System Component)", Category = "AVUtils"))
struct AVUTILITIESGAMEPLAYABILITIES_API FAV_HasMatchingTagASCStateTreeCondition : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FAV_HasMatchingTagASCStateTreeConditionInstanceData;

	//~ FStateTreeConditionCommonBase
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
	
#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
	virtual FName GetIconName() const override { return FName("GameplayAbilitiesEditor|ClassIcon.AbilitySystemComponent"); }
#endif // WITH_EDITOR
};
