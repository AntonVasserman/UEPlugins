// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayAbilities/Attributes/AV_ResourceAttributeSet.h"

#include "AV_ResourceComponent.generated.h"

class UAbilitySystemComponent;
class UAV_ResourceViewModel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAV_OnResourceViewModelInstantiatedDelegate, UAV_ResourceViewModel*, ResourceViewModel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAV_OnResourceValueChangedDelegate, int32, NewValue);

UCLASS(Abstract)
class AVUTILITIESGAMEPLAYABILITIES_API UAV_ResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAV_ResourceComponent();
	
	UPROPERTY(BlueprintAssignable)
	FAV_OnResourceViewModelInstantiatedDelegate OnResourceViewModelInstantiated;

	UPROPERTY(BlueprintAssignable)
	FAV_OnResourceValueChangedDelegate OnResourceValueChanged;
	
	UFUNCTION(BlueprintCallable, Category = "Resource")
	virtual void InitializeWithAbilitySystem(UAbilitySystemComponent* InAbilitySystemComponent);
	
	UFUNCTION(BlueprintCallable, Category = "Resource")
	void UnInitializeFromAbilitySystem();
	
	UFUNCTION(BlueprintCallable, Category = "Resource|ViewModel")
	void InitializeViewModel();
	
	UFUNCTION(BlueprintCallable, Category = "Resource")
	FORCEINLINE float GetValue() const { return ResourceAttributeSet->GetValue(); }

	UFUNCTION(BlueprintCallable, Category = "Resource")
	FORCEINLINE float GetMaxValue() const { return ResourceAttributeSet->GetMaxValue(); }

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY()
	TObjectPtr<const UAV_ResourceAttributeSet> ResourceAttributeSet = nullptr;
	TSubclassOf<UAV_ResourceAttributeSet> ResourceAttributeSetClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource|ViewModel")
	FName ResourceViewModelContextName;

	UPROPERTY(BlueprintReadOnly, Category = "Resource|ViewModel")
	TObjectPtr<UAV_ResourceViewModel> ResourceViewModel = nullptr;
	
	virtual void ResourceValueChanged(float OldValue, float NewValue) { }
	
	//~ UActorComponent
};
