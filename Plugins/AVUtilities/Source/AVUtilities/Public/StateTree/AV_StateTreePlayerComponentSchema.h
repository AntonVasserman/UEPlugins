// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/StateTreeComponentSchema.h"
#include "AV_StateTreePlayerComponentSchema.generated.h"

/*
* State tree schema to be used with AV_StateTreePlayerComponent. 
* It guarantees access to an PlayerController and the Actor context value can be used to access the controlled pawn.
*/
UCLASS(BlueprintType, EditInlineNew, CollapseCategories, Meta = (DisplayName = "StateTree Player Component", CommonSchema))
class AVUTILITIES_API UAV_StateTreePlayerComponentSchema : public UStateTreeComponentSchema
{
	GENERATED_BODY()
public:
	UAV_StateTreePlayerComponentSchema(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	/** PlayerController class the StateTree is expected to run on. Allows binding to specific Actor class' properties. */
	UPROPERTY(EditAnywhere, Category = "Defaults", NoClear)
	TSubclassOf<APlayerController> PlayerControllerClass = nullptr;

	//~ UStateTreeComponentSchema
public:
	virtual void PostLoad() override;
	static bool SetContextRequirements(UBrainComponent& BrainComponent, FStateTreeExecutionContext& Context, bool bLogErrors = false);

#if WITH_EDITOR
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR
};
