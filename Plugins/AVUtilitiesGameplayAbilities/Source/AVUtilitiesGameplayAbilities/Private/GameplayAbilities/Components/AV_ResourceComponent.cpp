// Copyright Anton Vasserman, All Rights Reserved.


#include "GameplayAbilities/Components/AV_ResourceComponent.h"

#include "GameplayEffectTypes.h"
#include "MVVMGameSubsystem.h"
#include "Engine/GameInstance.h"
#include "Types/MVVMViewModelCollection.h"
#include "Types/MVVMViewModelContext.h"
#include "UI/ViewModel/AV_ResourceViewModel.h"

UAV_ResourceComponent::UAV_ResourceComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void UAV_ResourceComponent::InitializeWithAbilitySystem(UAbilitySystemComponent* InAbilitySystemComponent)
{
	const AActor* OwningActor = GetOwner();
	check(OwningActor);
	checkf(AbilitySystemComponent == nullptr, TEXT("%s: %s for owner %s has already been initialized with an ability system"), __FUNCTIONW__, *ResourceAttributeSet.GetClass()->GetName(), *OwningActor->GetName());
	checkf(InAbilitySystemComponent != nullptr, TEXT("%s: Cannot initialize %s for owner %s, with null input ability system!"), __FUNCTIONW__, *ResourceAttributeSet.GetClass()->GetName(), *OwningActor->GetName());
	
	AbilitySystemComponent = InAbilitySystemComponent;
	checkf(ResourceAttributeSetClass != nullptr, TEXT("%s: Cannot initialize %s for owner %s, because ResourceAttributeSetClass is not set!"), __FUNCTIONW__, *ResourceAttributeSet.GetClass()->GetName(), *OwningActor->GetName());
	ResourceAttributeSet = Cast<UAV_ResourceAttributeSet>(AbilitySystemComponent->GetAttributeSet(ResourceAttributeSetClass));
	
	checkf(ResourceAttributeSet != nullptr, TEXT("%s: Cannot initialize %s for owner %s, with null ResourceAttributeSet on the ability system."), __FUNCTIONW__, *ResourceAttributeSet.GetClass()->GetName(), *OwningActor->GetName());

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ResourceAttributeSet->GetValueAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			if (ResourceViewModel != nullptr)
			{
				ResourceViewModel->SetCurrentValue(Data.NewValue);
			}

			ResourceValueChanged(Data.OldValue, Data.NewValue);
			OnResourceValueChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ResourceAttributeSet->GetMaxValueAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			if (ResourceViewModel != nullptr)
			{
				ResourceViewModel->SetMaxValue(Data.NewValue);
			}
		});
}

void UAV_ResourceComponent::UnInitializeFromAbilitySystem()
{
	if (ResourceAttributeSet != nullptr)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ResourceAttributeSet->GetValueAttribute()).RemoveAll(this);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ResourceAttributeSet->GetMaxValueAttribute()).RemoveAll(this);
		
		ResourceAttributeSet = nullptr;
	}
	
	AbilitySystemComponent = nullptr;
}

void UAV_ResourceComponent::InitializeViewModel()
{
	const UMVVMGameSubsystem* ViewModelGameSubsystem = GetOwner()->GetGameInstance()->GetSubsystem<UMVVMGameSubsystem>();
	check(ViewModelGameSubsystem);

	UMVVMViewModelCollectionObject* GlobalViewModelCollection = ViewModelGameSubsystem->GetViewModelCollection();
	check(GlobalViewModelCollection);
	
	FMVVMViewModelContext NewResourceViewModelContext;
	NewResourceViewModelContext.ContextClass = UAV_ResourceViewModel::StaticClass();
	NewResourceViewModelContext.ContextName = ResourceViewModelContextName;
	
	if (NewResourceViewModelContext.IsValid())
	{
		UAV_ResourceViewModel* NewResourceViewModel = NewObject<UAV_ResourceViewModel>();
		NewResourceViewModel->SetCurrentValue(ResourceAttributeSet->GetValue());
		NewResourceViewModel->SetMaxValue(ResourceAttributeSet->GetMaxValue());

		ResourceViewModel = NewResourceViewModel;
		GlobalViewModelCollection->AddViewModelInstance(NewResourceViewModelContext, NewResourceViewModel);
		
		OnResourceViewModelInstantiated.Broadcast(NewResourceViewModel);
	}
}
