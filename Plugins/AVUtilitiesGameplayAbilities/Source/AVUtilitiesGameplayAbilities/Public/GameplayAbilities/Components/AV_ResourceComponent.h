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

UENUM()
enum class EAV_ResourceState : uint8
{
	Full		UMETA(DisplayName = "Full"),
	Normal		UMETA(DisplayName = "Normal"),
	Critical	UMETA(DisplayName = "Critical"),
	Depleted	UMETA(DisplayName = "Depleted"),
};

USTRUCT(BlueprintType)
struct FAV_ResourceGameplayTags
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "")
	FGameplayTag Full;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "")
	FGameplayTag Normal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "")
	FGameplayTag Critical;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "")
	FGameplayTag Depleted;
};

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
	FAV_ResourceGameplayTags ResourceGameplayTags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource|ViewModel")
	FName ResourceViewModelContextName;

	UPROPERTY(BlueprintReadOnly, Category = "Resource|ViewModel")
	TObjectPtr<UAV_ResourceViewModel> ResourceViewModel = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Resource", Meta = (AllowPrivateAccess = "true", ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float CriticalSectionThresholdInPercentage = 0.2f;
	
	// Abstract functions meant to be implemented by deriving Resource Components
	virtual void ResourceStateChanged(EAV_ResourceState OldState, EAV_ResourceState NewState) { }
	virtual void ResourceValueChanged(float OldValue, float NewValue) { }
	
private:
	EAV_ResourceState EvaluateResourceState(float Value) const;
	FGameplayTag GetResourceGameplayTag(EAV_ResourceState State) const;
	
	//~ UActorComponent
};
