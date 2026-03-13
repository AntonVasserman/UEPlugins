// Copyright Anton Vasserman, All Rights Reserved.


#include "GameplayAbilities/Data/AV_AbilitySet_GrantedHandlers.h"

#include "AbilitySystemComponent.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayAbilitySpecHandle.h"

void FAV_AbilitySet_GrantedHandlers::AddAttributeSet(UAttributeSet* AttributeSet)
{
	check(AttributeSet);
	AttributeSets.Add(AttributeSet);
}

void FAV_AbilitySet_GrantedHandlers::AddActiveGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle)
{
	if (Handle.IsValid())
	{
		ActiveGameplayEffectHandles.Add(Handle);
	}
}

void FAV_AbilitySet_GrantedHandlers::AddGameplayAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
	if (Handle.IsValid())
	{
		GameplayAbilitySpecHandles.Add(Handle);
	}
}

void FAV_AbilitySet_GrantedHandlers::RemoveAllFromAbilitySystem(UAbilitySystemComponent* AbilitySystem)
{
	check(AbilitySystem);

	RemoveGameplayAbilitiesFromAbilitySystem(AbilitySystem);
	RemoveActiveGameplayEffectsFromAbilitySystem(AbilitySystem);
	RemoveAttributeSetsFromAbilitySystem(AbilitySystem);
}

void FAV_AbilitySet_GrantedHandlers::RemoveAttributeSetsFromAbilitySystem(UAbilitySystemComponent* AbilitySystem)
{
	check(AbilitySystem);
	
	for (UAttributeSet* AttributeSet : AttributeSets)
	{
		AbilitySystem->RemoveSpawnedAttribute(AttributeSet);
	}
	
	AttributeSets.Reset();
}

void FAV_AbilitySet_GrantedHandlers::RemoveActiveGameplayEffectsFromAbilitySystem(UAbilitySystemComponent* AbilitySystem)
{
	check(AbilitySystem);
	
	for (const FActiveGameplayEffectHandle& Handle : ActiveGameplayEffectHandles)
	{
		if (Handle.IsValid())
		{
			AbilitySystem->RemoveActiveGameplayEffect(Handle);
		}
	}
	
	ActiveGameplayEffectHandles.Reset();
}

void FAV_AbilitySet_GrantedHandlers::RemoveGameplayAbilitiesFromAbilitySystem(UAbilitySystemComponent* AbilitySystem)
{
	check(AbilitySystem);
	
	for (const FGameplayAbilitySpecHandle& Handle : GameplayAbilitySpecHandles)
	{
		if (Handle.IsValid())
		{
			AbilitySystem->ClearAbility(Handle);
		}
	}
	
	GameplayAbilitySpecHandles.Reset();
}
