// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "AV_AbilitySet_GrantedHandlers.generated.h"

struct FActiveGameplayEffectHandle;
struct FGameplayAbilitySpecHandle;
class UAbilitySystemComponent;
class UAttributeSet;

/**
 *	Data used to store handles to what has been granted by the ability set.
 */
USTRUCT(BlueprintType)
struct FAV_AbilitySet_GrantedHandlers
{
	GENERATED_BODY()
	
	void AddAttributeSet(UAttributeSet* AttributeSet);
	void AddActiveGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle);
	void AddGameplayAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);

	void RemoveAllFromAbilitySystem(UAbilitySystemComponent* AbilitySystem);
	void RemoveAttributeSetsFromAbilitySystem(UAbilitySystemComponent* AbilitySystem);
	void RemoveActiveGameplayEffectsFromAbilitySystem(UAbilitySystemComponent* AbilitySystem);
	void RemoveGameplayAbilitiesFromAbilitySystem(UAbilitySystemComponent* AbilitySystem);

protected:
	// Handles to the granted attribute sets.
	UPROPERTY()
	TArray<TObjectPtr<UAttributeSet>> AttributeSets;

	// Handles to the granted gameplay effects.
	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> ActiveGameplayEffectHandles;

	// Handles to the granted abilities.
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> GameplayAbilitySpecHandles;
};
