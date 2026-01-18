// Copyright Anton Vasserman, All Rights Reserved.


#include "AV_GameUIManagerSubsystem.h"

#include "AV_GameUIPolicy.h"
#include "Engine/GameInstance.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AV_GameUIManagerSubsystem)

void UAV_GameUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (CurrentPolicy == nullptr && !DefaultUIPolicyClass.IsNull())
	{
		TSubclassOf<UAV_GameUIPolicy> PolicyClass = DefaultUIPolicyClass.LoadSynchronous();
		SwitchToPolicy(NewObject<UAV_GameUIPolicy>(this, PolicyClass));
	}
}

void UAV_GameUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();

	SwitchToPolicy(nullptr);
}

bool UAV_GameUIManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> ChildClasses;
		GetDerivedClasses(GetClass(), ChildClasses, false);

		// Only create an instance if there is no override implementation defined elsewhere
		return ChildClasses.Num() == 0;
	}

	return false;
}

void UAV_GameUIManagerSubsystem::NotifyPlayerAdded(ULocalPlayer* LocalPlayer)
{
	if (ensure(LocalPlayer) && CurrentPolicy != nullptr)
	{
		CurrentPolicy->NotifyPlayerAdded(LocalPlayer);
	}
}

void UAV_GameUIManagerSubsystem::NotifyPlayerRemoved(ULocalPlayer* LocalPlayer)
{
	if (LocalPlayer && CurrentPolicy != nullptr)
	{
		CurrentPolicy->NotifyPlayerRemoved(LocalPlayer);
	}
}

void UAV_GameUIManagerSubsystem::NotifyPlayerDestroyed(ULocalPlayer* LocalPlayer)
{
	if (LocalPlayer && CurrentPolicy != nullptr)
	{
		CurrentPolicy->NotifyPlayerDestroyed(LocalPlayer);
	}
}

void UAV_GameUIManagerSubsystem::SwitchToPolicy(UAV_GameUIPolicy* InPolicy)
{
	if (CurrentPolicy != InPolicy)
	{
		CurrentPolicy = InPolicy;
	}
}
