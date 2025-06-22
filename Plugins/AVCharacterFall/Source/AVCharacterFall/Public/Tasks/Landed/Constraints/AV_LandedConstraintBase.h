// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AV_LandedConstraintBase.generated.h"

USTRUCT(BlueprintType)
struct AVCHARACTERFALL_API FAV_LandedConstraintContext
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACharacter> Character;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> HitActor;
};

UCLASS(Abstract, Blueprintable, EditInlineNew, Meta = (DisplayName = "Landed Constraint Base"))
class AVCHARACTERFALL_API UAV_LandedConstraintBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	bool TestConstraint(const FAV_LandedConstraintContext& ConstraintContext) const;
	virtual bool TestConstraint_Implementation(const FAV_LandedConstraintContext& ConstraintContext) const { return false; }
};
