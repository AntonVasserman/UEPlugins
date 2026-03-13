// Copyright Anton Vasserman, All Rights Reserved.


#include "GameplayAbilities/Data/AV_AbilitySet_GameplayEffect.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayAbilities/Data/AV_AbilitySet_GrantedHandlers.h"

void FAV_AbilitySet_GameplayEffect::GiveToAbilitySystem(UAbilitySystemComponent* AbilitySystem, FAV_AbilitySet_GrantedHandlers* OutGrantedHandlers) const
{
	if (!IsValid(GameplayEffectClass)) return;

	const UGameplayEffect* GameplayEffectCDO = GameplayEffectClass->GetDefaultObject<UGameplayEffect>();
	const FActiveGameplayEffectHandle GameplayEffectHandle = AbilitySystem->ApplyGameplayEffectToSelf(GameplayEffectCDO, EffectLevel, AbilitySystem->MakeEffectContext());

	if (OutGrantedHandlers)
	{
		OutGrantedHandlers->AddActiveGameplayEffectHandle(GameplayEffectHandle);
	}
}
