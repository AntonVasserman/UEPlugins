// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AV_FallingTaskBase.generated.h"

class UAV_CharacterFallComponent;

USTRUCT(BlueprintType)
struct AVCHARACTERFALL_API FAV_FallingTaskContext
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACharacter> Character;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAV_CharacterFallComponent> FallingComponent;
};

UCLASS(Abstract, Blueprintable, EditInlineNew, Meta = (DisplayName = "Falling Task Base"))
class AVCHARACTERFALL_API UAV_FallingTaskBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void ExecuteTask(const FAV_FallingTaskContext& TaskContext) const;
	virtual void ExecuteTask_Implementation(const FAV_FallingTaskContext& TaskContext) const {}
};
