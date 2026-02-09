// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeConditionBase.h"

#include "AV_GameplayTagEqualsStateTreeCondition.generated.h"

USTRUCT()
struct AVUTILITIES_API FAV_GameplayTagEqualsStateTreeConditionInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Input")
	FGameplayTag Left;

	UPROPERTY(EditAnywhere, Category = "Parameter")
	FGameplayTag Right;
	
	UPROPERTY(EditAnywhere, Category = "Parameter")
	bool bInvert = false;
};

USTRUCT(Meta = (DisplayName = "Gameplay Tag Equals"))
struct AVUTILITIES_API FAV_GameplayTagEqualsStateTreeCondition : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()
	
	using FInstanceDataType = FAV_GameplayTagEqualsStateTreeConditionInstanceData;
	
	//~ FStateTreeConditionCommonBase
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
	
#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
#endif // WITH_EDITOR
};
