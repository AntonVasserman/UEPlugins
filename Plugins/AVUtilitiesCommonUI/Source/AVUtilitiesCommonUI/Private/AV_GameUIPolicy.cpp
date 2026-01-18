// Copyright Anton Vasserman, All Rights Reserved.


#include "AV_GameUIPolicy.h"

#include "AV_GameUIManagerSubsystem.h"
#include "AV_LogAVUtilitiesCommonUI.h"
#include "AV_PrimaryGameLayout.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AV_GameUIPolicy)

/*static*/ UAV_GameUIPolicy* UAV_GameUIPolicy::GetGameUIPolicy(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			if (UAV_GameUIManagerSubsystem* UIManager = UGameInstance::GetSubsystem<UAV_GameUIManagerSubsystem>(GameInstance))
			{
				return UIManager->GetCurrentUIPolicy();
			}
		}
	}

	return nullptr;
}

UAV_GameUIManagerSubsystem* UAV_GameUIPolicy::GetOwningUIManager() const
{
	return CastChecked<UAV_GameUIManagerSubsystem>(GetOuter());
}

UAV_PrimaryGameLayout* UAV_GameUIPolicy::GetRootLayout(const ULocalPlayer* LocalPlayer) const
{
	const FAV_RootViewportLayoutInfo* LayoutInfo = RootViewportLayouts.FindByKey(LocalPlayer);
	return LayoutInfo ? LayoutInfo->RootLayout : nullptr;
}

void UAV_GameUIPolicy::NotifyPlayerAdded(ULocalPlayer* LocalPlayer)
{
	LocalPlayer->OnPlayerControllerChanged().AddWeakLambda(this, [this, LocalPlayer](APlayerController* PlayerController)
	{
		NotifyPlayerRemoved(LocalPlayer);

		if (FAV_RootViewportLayoutInfo* LayoutInfo = RootViewportLayouts.FindByKey(LocalPlayer))
		{
			AddLayoutToViewport(LocalPlayer, LayoutInfo->RootLayout);
			LayoutInfo->bAddedToViewport = true;
		}
		else
		{
			CreateLayoutWidget(LocalPlayer);
		}
	});

	if (FAV_RootViewportLayoutInfo* LayoutInfo = RootViewportLayouts.FindByKey(LocalPlayer))
	{
		AddLayoutToViewport(LocalPlayer, LayoutInfo->RootLayout);
		LayoutInfo->bAddedToViewport = true;
	}
	else
	{
		CreateLayoutWidget(LocalPlayer);
	}
}

void UAV_GameUIPolicy::NotifyPlayerRemoved(ULocalPlayer* LocalPlayer)
{
	if (FAV_RootViewportLayoutInfo* LayoutInfo = RootViewportLayouts.FindByKey(LocalPlayer))
	{
		RemoveLayoutFromViewport(LocalPlayer, LayoutInfo->RootLayout);
		LayoutInfo->bAddedToViewport = false;
	}
}

void UAV_GameUIPolicy::NotifyPlayerDestroyed(ULocalPlayer* LocalPlayer)
{
	NotifyPlayerRemoved(LocalPlayer);
	LocalPlayer->OnPlayerControllerChanged().RemoveAll(this);
	const int32 LayoutInfoIdx = RootViewportLayouts.IndexOfByKey(LocalPlayer);
	if (LayoutInfoIdx != INDEX_NONE)
	{
		UAV_PrimaryGameLayout* Layout = RootViewportLayouts[LayoutInfoIdx].RootLayout;
		RootViewportLayouts.RemoveAt(LayoutInfoIdx);

		RemoveLayoutFromViewport(LocalPlayer, Layout);

		OnRootLayoutReleased(LocalPlayer, Layout);
	}
}

void UAV_GameUIPolicy::AddLayoutToViewport(ULocalPlayer* LocalPlayer, UAV_PrimaryGameLayout* Layout)
{
	UE_LOG(AV_LogAVUtilitiesCommonUI, Log, TEXT("[%s] is adding player [%s]'s root layout [%s] to the viewport"), *GetName(), *GetNameSafe(LocalPlayer), *GetNameSafe(Layout));

	Layout->SetPlayerContext(FLocalPlayerContext(LocalPlayer));
	Layout->AddToPlayerScreen(1000);

	OnRootLayoutAddedToViewport(LocalPlayer, Layout);
}

void UAV_GameUIPolicy::RemoveLayoutFromViewport(ULocalPlayer* LocalPlayer, UAV_PrimaryGameLayout* Layout)
{
	TWeakPtr<SWidget> LayoutSlateWidget = Layout->GetCachedWidget();
	if (LayoutSlateWidget.IsValid())
	{
		UE_LOG(AV_LogAVUtilitiesCommonUI, Log, TEXT("[%s] is removing player [%s]'s root layout [%s] from the viewport"), *GetName(), *GetNameSafe(LocalPlayer), *GetNameSafe(Layout));

		Layout->RemoveFromParent();
		if (LayoutSlateWidget.IsValid())
		{
			UE_LOG(AV_LogAVUtilitiesCommonUI, Log, TEXT("Player [%s]'s root layout [%s] has been removed from the viewport, but other references to its underlying Slate widget still exist. Noting in case we leak it."), *GetNameSafe(LocalPlayer), *GetNameSafe(Layout));
		}

		OnRootLayoutRemovedFromViewport(LocalPlayer, Layout);
	}
}

void UAV_GameUIPolicy::OnRootLayoutAddedToViewport(ULocalPlayer* LocalPlayer, UAV_PrimaryGameLayout* Layout)
{
#if WITH_EDITOR
	if (GIsEditor && LocalPlayer->IsPrimaryPlayer())
	{
		// So our controller will work in PIE without needing to click in the viewport
		FSlateApplication::Get().SetUserFocusToGameViewport(0);
	}
#endif // WITH_EDITOR
}

void UAV_GameUIPolicy::OnRootLayoutRemovedFromViewport(ULocalPlayer* LocalPlayer, UAV_PrimaryGameLayout* Layout)
{
	
}

void UAV_GameUIPolicy::OnRootLayoutReleased(ULocalPlayer* LocalPlayer, UAV_PrimaryGameLayout* Layout)
{
	
}

void UAV_GameUIPolicy::CreateLayoutWidget(ULocalPlayer* LocalPlayer)
{
	if (APlayerController* PlayerController = LocalPlayer->GetPlayerController(GetWorld()))
	{
		TSubclassOf<UAV_PrimaryGameLayout> LayoutWidgetClass = GetLayoutWidgetClass(LocalPlayer);
		if (ensure(LayoutWidgetClass && !LayoutWidgetClass->HasAnyClassFlags(CLASS_Abstract)))
		{
			UAV_PrimaryGameLayout* NewLayoutObject = CreateWidget<UAV_PrimaryGameLayout>(PlayerController, LayoutWidgetClass);
			RootViewportLayouts.Emplace(LocalPlayer, NewLayoutObject, true);
			
			AddLayoutToViewport(LocalPlayer, NewLayoutObject);
		}
	}
}

TSubclassOf<UAV_PrimaryGameLayout> UAV_GameUIPolicy::GetLayoutWidgetClass(ULocalPlayer* LocalPlayer)
{
	return LayoutClass.LoadSynchronous();
}

//~ UObject

UWorld* UAV_GameUIPolicy::GetWorld() const
{
	return GetOwningUIManager()->GetGameInstance()->GetWorld();
}

