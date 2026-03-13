// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"

#include "AV_AbilitySet_AttributeSet.generated.h"

struct FAV_AbilitySet_GrantedHandlers;
class UAbilitySystemComponent;
class UAttributeSet;

/**
 *	Data used by the ability set to grant attribute sets.
 */
USTRUCT(BlueprintType)
struct FAV_AbilitySet_AttributeSet
{
	GENERATED_BODY()

	// Gameplay attribute to grant
	UPROPERTY(EditDefaultsOnly, Category = "")
	TSubclassOf<UAttributeSet> AttributeSetClass;
	
	void GiveToAbilitySystem(UAbilitySystemComponent* AbilitySystem, FAV_AbilitySet_GrantedHandlers* OutGrantedHandlers) const;
};
