// Copyright Anton Vasserman, All Rights Reserved.


#include "GameplayAbilities/Attributes/AV_ResourceAttributeSet.h"

#include "GameplayEffectExtension.h"

//~ UAttributeSet

void UAV_ResourceAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetValueAttribute())
	{
		SetValue(FMath::Clamp(GetOwningAbilitySystemComponent()->HasMatchingGameplayTag(ResourceInfiniteGameplayTag) ? GetMaxValue() : GetValue(), 0.f, GetMaxValue()));
	}
}

void UAV_ResourceAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetValueAttribute())
	{
		NewValue = FMath::Clamp(GetOwningAbilitySystemComponent()->HasMatchingGameplayTag(ResourceInfiniteGameplayTag) ? GetMaxValue() : NewValue, 0.f, GetMaxValue());
	}
}
