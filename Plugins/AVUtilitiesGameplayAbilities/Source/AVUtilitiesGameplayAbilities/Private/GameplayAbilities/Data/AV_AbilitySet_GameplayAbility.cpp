// Copyright Anton Vasserman, All Rights Reserved.


#include "GameplayAbilities/Data/AV_AbilitySet_GameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "GameplayAbilitySpecHandle.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilities/Data/AV_AbilitySet_GrantedHandlers.h"

void FAV_AbilitySet_GameplayAbility::GiveToAbilitySystem(UAbilitySystemComponent* AbilitySystem, FAV_AbilitySet_GrantedHandlers* OutGrantedHandlers) const
{
	if (!IsValid(AbilityClass)) return;
	
	UGameplayAbility* AbilityCDO = AbilityClass->GetDefaultObject<UGameplayAbility>();
	FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityLevel);
	for (const FGameplayTag& Tag : TagsToAddOnGranting)
	{
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(Tag);
	}
	
	const FGameplayAbilitySpecHandle AbilitySpecHandle = bActivateOnceOnGranting ? 
		AbilitySystem->GiveAbilityAndActivateOnce(AbilitySpec) :
		AbilitySystem->GiveAbility(AbilitySpec);
	
	if (OutGrantedHandlers)
	{
		OutGrantedHandlers->AddGameplayAbilitySpecHandle(AbilitySpecHandle);
	}
}
