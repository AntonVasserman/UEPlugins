// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "AV_GameUIManagerSubsystem.generated.h"

#define UE_API AVUTILITIESCOMMONUI_API

class UAV_GameUIPolicy;
class ULocalPlayer;

/**
 * This manager is intended to be replaced by whatever your game needs to
 * actually create, so this class is abstract to prevent it from being created.
 * 
 * If you just need the basic functionality you will start by sublcassing this
 * subsystem in your own game.
 */
UCLASS(MinimalAPI, Abstract, config = Game)
class UAV_GameUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	const UAV_GameUIPolicy* GetCurrentUIPolicy() const { return CurrentPolicy; }
	UAV_GameUIPolicy* GetCurrentUIPolicy() { return CurrentPolicy; }
	UE_API virtual void NotifyPlayerAdded(ULocalPlayer* LocalPlayer);
	UE_API virtual void NotifyPlayerRemoved(ULocalPlayer* LocalPlayer);
	UE_API virtual void NotifyPlayerDestroyed(ULocalPlayer* LocalPlayer);
	
protected:
	UE_API void SwitchToPolicy(UAV_GameUIPolicy* InPolicy);

private:
	UPROPERTY(Transient)
	TObjectPtr<UAV_GameUIPolicy> CurrentPolicy = nullptr;

	UPROPERTY(EditAnywhere, Config, Category = "Config")
	TSoftClassPtr<UAV_GameUIPolicy> DefaultUIPolicyClass;
	
	//~ UGameInstanceSubsystem
public:
	UE_API virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UE_API virtual void Deinitialize() override;
	UE_API virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
};

#undef UE_API
