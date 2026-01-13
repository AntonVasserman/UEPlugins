// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/StateTreeComponent.h"
#include "AV_StateTreePlayerComponent.generated.h"

/**
* State tree component designed to be run on a PlayerController.
* It uses the AV_StateTreePlayerComponentSchema that guarantees access to the PlayerController.
*/
UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class AVUTILITIES_API UAV_StateTreePlayerComponent : public UStateTreeComponent
{
	GENERATED_BODY()
public:
	//~ UStateTreeComponent
	virtual TSubclassOf<UStateTreeSchema> GetSchema() const override;
	virtual bool SetContextRequirements(FStateTreeExecutionContext& Context, bool bLogErrors = false) override;
};
