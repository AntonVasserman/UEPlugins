// Copyright Anton Vasserman, All Rights Reserved.


#include "GameplayAbilities/Data/AV_AbilitySet.h"

#include "AbilitySystemComponent.h"
#include "AVUtilitiesGameplayAbilities.h"
#include "GameplayAbilities/Data/AV_AbilitySet_AttributeSet.h"
#include "GameplayAbilities/Data/AV_AbilitySet_GameplayAbility.h"
#include "GameplayAbilities/Data/AV_AbilitySet_GameplayEffect.h"

void UAV_AbilitySet::GiveToAbilitySystem(UAbilitySystemComponent* AbilitySystem, FAV_AbilitySet_GrantedHandlers* OutGrantedHandlers) const
{
	check(AbilitySystem);

	GiveAttributeSetsToAbilitySystem(AbilitySystem, OutGrantedHandlers);
	GiveGameplayEffectsToAbilitySystem(AbilitySystem, OutGrantedHandlers);
	GiveGameplayAbilitiesToAbilitySystem(AbilitySystem, OutGrantedHandlers);
}

void UAV_AbilitySet::GiveAttributeSetsToAbilitySystem(UAbilitySystemComponent* AbilitySystem, FAV_AbilitySet_GrantedHandlers* OutGrantedHandlers) const
{
	for (int32 i = 0; i < GrantedAttributes.Num(); i++)
	{
		const FAV_AbilitySet_AttributeSet& SetToGrant = GrantedAttributes[i];

		if (!IsValid(SetToGrant.AttributeSetClass))
		{
			AV_LOG_UTILSGAS_EXTENDED(Error, "GrantedAttributes[%d] on ability set: '%s' is not valid", i, *GetNameSafe(this));
			continue;
		}

		SetToGrant.GiveToAbilitySystem(AbilitySystem, OutGrantedHandlers);
	}
}

void UAV_AbilitySet::GiveGameplayEffectsToAbilitySystem(UAbilitySystemComponent* AbilitySystem, FAV_AbilitySet_GrantedHandlers* OutGrantedHandlers) const
{
	for (int32 i = 0; i < GrantedGameplayEffects.Num(); i++)
	{
		const FAV_AbilitySet_GameplayEffect& EffectToGrant = GrantedGameplayEffects[i];

		if (!IsValid(EffectToGrant.GameplayEffectClass))
		{
			AV_LOG_UTILSGAS_EXTENDED(Error, "GrantedGameplayEffects[%d] on ability set: '%s' is not valid", i, *GetNameSafe(this));
			continue;
		}

		EffectToGrant.GiveToAbilitySystem(AbilitySystem, OutGrantedHandlers);
	}
}

void UAV_AbilitySet::GiveGameplayAbilitiesToAbilitySystem(UAbilitySystemComponent* AbilitySystem, FAV_AbilitySet_GrantedHandlers* OutGrantedHandlers) const
{
	for (int32 i = 0; i < GrantedGameplayAbilities.Num(); i++)
	{
		const FAV_AbilitySet_GameplayAbility& AbilityToGrant = GrantedGameplayAbilities[i];

		if (!IsValid(AbilityToGrant.AbilityClass))
		{
			AV_LOG_UTILSGAS_EXTENDED(Error, "GrantedGameplayAbilities[%d] on ability set: '%s' is not valid", i, *GetNameSafe(this));
			continue;
		}
		
		AbilityToGrant.GiveToAbilitySystem(AbilitySystem, OutGrantedHandlers);
	}
}
