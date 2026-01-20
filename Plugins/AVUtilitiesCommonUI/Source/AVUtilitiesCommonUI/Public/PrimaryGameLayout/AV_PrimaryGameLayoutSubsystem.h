// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "AV_PrimaryGameLayoutSubsystem.generated.h"

#define UE_API AVUTILITIESCOMMONUI_API

class UAV_PrimaryGameLayout;
class ULocalPlayer;

/**
 * TODO
 */
USTRUCT()
struct FAV_RootViewportLayoutInfo
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	TObjectPtr<ULocalPlayer> LocalPlayer = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UAV_PrimaryGameLayout> RootLayout = nullptr;

	UPROPERTY(Transient)
	bool bAddedToViewport = false;

	FAV_RootViewportLayoutInfo()
	{
	}
	
	FAV_RootViewportLayoutInfo(ULocalPlayer* InLocalPlayer, UAV_PrimaryGameLayout* InRootLayout, bool bIsInViewport)
		: LocalPlayer(InLocalPlayer)
		, RootLayout(InRootLayout)
		, bAddedToViewport(bIsInViewport)
	{
	}

	bool operator==(const ULocalPlayer* OtherLocalPlayer) const { return LocalPlayer == OtherLocalPlayer; }
};

/**
 * TODO
 */
UCLASS(MinimalAPI, Config = Game)
class UAV_PrimaryGameLayoutSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UE_API virtual void NotifyPlayerAdded(ULocalPlayer* LocalPlayer);
	UE_API virtual void NotifyPlayerRemoved(ULocalPlayer* LocalPlayer);
	UE_API virtual void NotifyPlayerDestroyed(ULocalPlayer* LocalPlayer);
	
	UE_API UAV_PrimaryGameLayout* GetRootLayout(const ULocalPlayer* LocalPlayer) const;
	
protected:
	UE_API void AddLayoutToViewport(ULocalPlayer* LocalPlayer, UAV_PrimaryGameLayout* Layout);
	UE_API void RemoveLayoutFromViewport(ULocalPlayer* LocalPlayer, UAV_PrimaryGameLayout* Layout);
	
	UE_API virtual void OnRootLayoutAddedToViewport(ULocalPlayer* LocalPlayer, UAV_PrimaryGameLayout* Layout);
	UE_API virtual void OnRootLayoutRemovedFromViewport(ULocalPlayer* LocalPlayer, UAV_PrimaryGameLayout* Layout);
	UE_API virtual void OnRootLayoutReleased(ULocalPlayer* LocalPlayer, UAV_PrimaryGameLayout* Layout);

	UE_API void CreateLayoutWidget(ULocalPlayer* LocalPlayer);
	UE_API TSubclassOf<UAV_PrimaryGameLayout> GetLayoutWidgetClass(ULocalPlayer* LocalPlayer);
	
private:
	UPROPERTY()
	TSoftClassPtr<UAV_PrimaryGameLayout> LayoutClass;
	
	UPROPERTY(Transient)
	TArray<FAV_RootViewportLayoutInfo> RootViewportLayouts;
	
	//~ UGameInstanceSubsystem
public:
	UE_API virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UE_API virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
};

#undef UE_API
