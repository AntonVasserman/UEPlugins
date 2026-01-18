// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "Engine/World.h"

#include "AV_GameUIPolicy.generated.h"

#define UE_API AVUTILITIESCOMMONUI_API

class UAV_GameUIManagerSubsystem;
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
UCLASS(MinimalAPI, Abstract, Blueprintable, Within = AV_GameUIManagerSubsystem)
class UAV_GameUIPolicy : public UObject
{
	GENERATED_BODY()

public:
	template <typename GameUIPolicyClass = UAV_GameUIPolicy>
	static GameUIPolicyClass* GetGameUIPolicyAs(const UObject* WorldContextObject)
	{
		return Cast<GameUIPolicyClass>(GetGameUIPolicy(WorldContextObject));
	}
	static UE_API UAV_GameUIPolicy* GetGameUIPolicy(const UObject* WorldContextObject);

	UE_API UAV_GameUIManagerSubsystem* GetOwningUIManager() const;
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
	UPROPERTY(EditAnywhere, Category = "")
	TSoftClassPtr<UAV_PrimaryGameLayout> LayoutClass;

	UPROPERTY(Transient)
	TArray<FAV_RootViewportLayoutInfo> RootViewportLayouts;

	UE_API void NotifyPlayerAdded(ULocalPlayer* LocalPlayer);
	UE_API void NotifyPlayerRemoved(ULocalPlayer* LocalPlayer);
	UE_API void NotifyPlayerDestroyed(ULocalPlayer* LocalPlayer);

	friend class UAV_GameUIManagerSubsystem;
	
	//~ UObject
public:
	UE_API virtual UWorld* GetWorld() const override;
};

#undef UE_API
