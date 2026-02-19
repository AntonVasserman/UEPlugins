// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"

#include "AV_ResourceViewModel.generated.h"

UCLASS()
class AVUTILITIESGAMEPLAYABILITIES_API UAV_ResourceViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, FieldNotify, Category = "GameplayAbilities|Resource")
	float GetCurrentValue() const { return CurrentValue; }

	UFUNCTION(BlueprintCallable, Category = "GameplayAbilities|Resource")
	void SetCurrentValue(float NewCurrentValue);

	UFUNCTION(BlueprintPure, FieldNotify, Category = "GameplayAbilities|Resource")
	float GetMaxValue() const { return MaxValue; }

	UFUNCTION(BlueprintCallable, Category = "GameplayAbilities|Resource")
	void SetMaxValue(float NewMaxValue);

	UFUNCTION(BlueprintPure, FieldNotify, Category = "GameplayAbilities|Resource")
	float GetValuePercentage() const;

private:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter = "GetCurrentValue", Setter = "SetCurrentValue", Category = "GameplayAbilities|Resource", Meta = (AllowPrivateAccess = "true"))
	float CurrentValue = 0.f;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter = "GetMaxValue", Setter = "SetCurrentValue", Category = "GameplayAbilities|Resource", Meta = (AllowPrivateAccess = "true"))
	float MaxValue = 0.f;
};
