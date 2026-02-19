// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

#include "AV_ResourceAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS(Abstract)
class AVUTILITIESGAMEPLAYABILITIES_API UAV_ResourceAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "GameplayAbilities|Attributes|Resource")
	virtual float GetValue() const { return 0.0f; }

	UFUNCTION(BlueprintCallable, Category = "GameplayAbilities|Attributes|Resource")
	virtual void SetValue(float NewValue) {}

	UFUNCTION(BlueprintCallable, Category = "GameplayAbilities|Attributes|Resource")
	virtual FGameplayAttribute GetValueAttribute() const { return nullptr; }

	UFUNCTION(BlueprintCallable, Category = "GameplayAbilities|Attributes|Resource")
	virtual float GetMaxValue() const { return 0.0f; }

	UFUNCTION(BlueprintCallable, Category = "GameplayAbilities|Attributes|Resource")
	virtual void SetMaxValue(float NewValue) {}

	UFUNCTION(BlueprintCallable, Category = "GameplayAbilities|Attributes|Resource")
	virtual FGameplayAttribute GetMaxValueAttribute() const { return nullptr; }

protected:
	FGameplayTag ResourceInfiniteGameplayTag = FGameplayTag::EmptyTag; // This needs to be overriden in the derived classes
	
	//~ UAttributeSet
protected:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
};
