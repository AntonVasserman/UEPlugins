// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"

#include "AV_AbilitySet_GameplayEffect.generated.h"

struct FAV_AbilitySet_GrantedHandlers;
class UAbilitySystemComponent;
class UGameplayEffect;

/**
 *	Data used by the ability set to grant gameplay effects.
 */
USTRUCT(BlueprintType)
struct FAV_AbilitySet_GameplayEffect
{
	GENERATED_BODY()
	
	// Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly, Category = "")
	TSubclassOf<UGameplayEffect> GameplayEffectClass = nullptr;

	// Level of gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly, Category = "")
	int32 EffectLevel = 1;
	
	void GiveToAbilitySystem(UAbilitySystemComponent* AbilitySystem, FAV_AbilitySet_GrantedHandlers* OutGrantedHandlers) const;
};
