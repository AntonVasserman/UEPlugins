// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeConditionBase.h"
#include "Templates/SubclassOf.h"
#include "AV_ObjectImplementsInterfaceStateTreeCondition.generated.h"

class UInterface;

USTRUCT()
struct AVUTILITIES_API FAV_ObjectImplementsInterfaceStateTreeConditionInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Inputs")
	TObjectPtr<UObject> Object;

	UPROPERTY(EditAnywhere, Category = "Parameter", Meta = (AllowAbstract = "true"))
	TSubclassOf<UInterface> Interface;

	UPROPERTY(EditAnywhere, Category = "Parameter")
	bool bInvert = false;
};

USTRUCT(Meta = (DisplayName = "Object Implements Interface"))
struct AVUTILITIES_API FAV_ObjectImplementsInterfaceStateTreeCondition : public FStateTreeConditionCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FAV_ObjectImplementsInterfaceStateTreeConditionInstanceData;
	
	//~ FStateTreeConditionCommonBase
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual bool TestCondition(FStateTreeExecutionContext& Context) const override;
	
#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
#endif // WITH_EDITOR
};
