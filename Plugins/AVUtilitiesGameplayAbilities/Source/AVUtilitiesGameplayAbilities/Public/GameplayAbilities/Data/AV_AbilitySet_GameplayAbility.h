// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Templates/SubclassOf.h"

#include "AV_AbilitySet_GameplayAbility.generated.h"

struct FAV_AbilitySet_GrantedHandlers;
class UAbilitySystemComponent;
class UGameplayAbility;

/**
 *	Data used by the ability set to grant gameplay abilities.
 */
USTRUCT(BlueprintType)
struct FAV_AbilitySet_GameplayAbility
{
	GENERATED_BODY()
	
	// Gameplay ability to grant.
	UPROPERTY(EditDefaultsOnly, Category = "")
	TSubclassOf<UGameplayAbility> AbilityClass = nullptr;

	// Level of ability to grant.
	UPROPERTY(EditDefaultsOnly, Category = "")
	int32 AbilityLevel = 1;
	
	// Additional Tags to add to the ability.
	UPROPERTY(EditDefaultsOnly, Category = "")
	TSet<FGameplayTag> TagsToAddOnGranting;
	
	// Indicates whether the ability should be activated once on granting.
	UPROPERTY(EditDefaultsOnly, Category = "")
	bool bActivateOnceOnGranting = false;
	
	void GiveToAbilitySystem(UAbilitySystemComponent* AbilitySystem, FAV_AbilitySet_GrantedHandlers* OutGrantedHandlers) const;
};
