// Copyright Anton Vasserman, All Rights Reserved.


#include "GameplayAbilities/Data/AV_AbilitySet_AttributeSet.h"

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayAbilities/Data/AV_AbilitySet_GrantedHandlers.h"

void FAV_AbilitySet_AttributeSet::GiveToAbilitySystem(UAbilitySystemComponent* AbilitySystem, FAV_AbilitySet_GrantedHandlers* OutGrantedHandlers) const
{
	if (!IsValid(AttributeSetClass)) return;

	UAttributeSet* NewSet = NewObject<UAttributeSet>(AbilitySystem->GetOwner(), AttributeSetClass);
	AbilitySystem->AddAttributeSetSubobject(NewSet);

	if (OutGrantedHandlers)
	{
		OutGrantedHandlers->AddAttributeSet(NewSet);
	}
}
