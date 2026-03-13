// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "AV_AbilitySet.generated.h"

struct FActiveGameplayEffectHandle;
struct FAV_AbilitySet_GrantedHandlers;
struct FAV_AbilitySet_GameplayAbility;
struct FAV_AbilitySet_GameplayEffect;
struct FAV_AbilitySet_AttributeSet;
struct FGameplayAbilitySpecHandle;
class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayAbility;
class UGameplayEffect;

/**
 *	The base class for Non-mutable data asset used to grant gameplay abilities and gameplay effects.
 */
UCLASS(BlueprintType, Const)
class AVUTILITIESGAMEPLAYABILITIES_API UAV_AbilitySet : public UDataAsset
{
	GENERATED_BODY()
	
public:
	void GiveToAbilitySystem(UAbilitySystemComponent* AbilitySystem, FAV_AbilitySet_GrantedHandlers* OutGrantedHandlers) const;
	
protected:
	// Attribute sets to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Attributes", Meta = (TitleProperty = AttributeSetClass))
	TArray<FAV_AbilitySet_AttributeSet> GrantedAttributes;
	
	// Gameplay effects to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "GameplayEffects", Meta = (TitleProperty = GameplayEffectClass))
	TArray<FAV_AbilitySet_GameplayEffect> GrantedGameplayEffects;
	
	// Gameplay abilities to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbilities", Meta = (TitleProperty = AbilityClass))
	TArray<FAV_AbilitySet_GameplayAbility> GrantedGameplayAbilities;
	
private:
	void GiveAttributeSetsToAbilitySystem(UAbilitySystemComponent* AbilitySystem, FAV_AbilitySet_GrantedHandlers* OutGrantedHandlers) const;
	void GiveGameplayEffectsToAbilitySystem(UAbilitySystemComponent* AbilitySystem, FAV_AbilitySet_GrantedHandlers* OutGrantedHandlers) const;
	void GiveGameplayAbilitiesToAbilitySystem(UAbilitySystemComponent* AbilitySystem, FAV_AbilitySet_GrantedHandlers* OutGrantedHandlers) const;
};