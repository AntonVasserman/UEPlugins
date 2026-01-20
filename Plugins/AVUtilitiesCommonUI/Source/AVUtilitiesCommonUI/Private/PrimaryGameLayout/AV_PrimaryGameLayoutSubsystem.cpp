// Copyright Anton Vasserman, All Rights Reserved.


#include "PrimaryGameLayout/AV_PrimaryGameLayoutSubsystem.h"

#include "Engine/GameInstance.h"
#include "Logging/AV_LogAVUtilitiesCommonUI.h"
#include "PrimaryGameLayout/AV_PrimaryGameLayout.h"
#include "PrimaryGameLayout/Settings/AV_PrimaryGameLayoutSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AV_PrimaryGameLayoutSubsystem)

void UAV_PrimaryGameLayoutSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (const TSoftClassPtr<UAV_PrimaryGameLayout> LayoutSoftClass = GetDefault<UAV_PrimaryGameLayoutSettings>()->PrimaryGameLayoutClass;
		!LayoutSoftClass.IsNull())
	{
		LayoutClass = LayoutSoftClass.LoadSynchronous();
	}
}

bool UAV_PrimaryGameLayoutSubsystem::ShouldCreateSubsystem(UObject* Outer) const
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

void UAV_PrimaryGameLayoutSubsystem::NotifyPlayerAdded(ULocalPlayer* LocalPlayer)
{
	if (ensure(LocalPlayer))
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
}

void UAV_PrimaryGameLayoutSubsystem::NotifyPlayerRemoved(ULocalPlayer* LocalPlayer)
{
	if (LocalPlayer)
	{
		if (FAV_RootViewportLayoutInfo* LayoutInfo = RootViewportLayouts.FindByKey(LocalPlayer))
		{
			RemoveLayoutFromViewport(LocalPlayer, LayoutInfo->RootLayout);
			LayoutInfo->bAddedToViewport = false;
		}
	}
}

void UAV_PrimaryGameLayoutSubsystem::NotifyPlayerDestroyed(ULocalPlayer* LocalPlayer)
{
	if (LocalPlayer)
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
}

UAV_PrimaryGameLayout* UAV_PrimaryGameLayoutSubsystem::GetRootLayout(const ULocalPlayer* LocalPlayer) const
{
	const FAV_RootViewportLayoutInfo* LayoutInfo = RootViewportLayouts.FindByKey(LocalPlayer);
	return LayoutInfo ? LayoutInfo->RootLayout : nullptr;
}

void UAV_PrimaryGameLayoutSubsystem::AddLayoutToViewport(ULocalPlayer* LocalPlayer, UAV_PrimaryGameLayout* Layout)
{
	UE_LOG(AV_LogAVUtilitiesCommonUI, Log, TEXT("[%s] is adding player [%s]'s root layout [%s] to the viewport"), *GetName(), *GetNameSafe(LocalPlayer), *GetNameSafe(Layout));

	Layout->SetPlayerContext(FLocalPlayerContext(LocalPlayer));
	Layout->AddToPlayerScreen(1000);

	OnRootLayoutAddedToViewport(LocalPlayer, Layout);
}

void UAV_PrimaryGameLayoutSubsystem::RemoveLayoutFromViewport(ULocalPlayer* LocalPlayer, UAV_PrimaryGameLayout* Layout)
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

void UAV_PrimaryGameLayoutSubsystem::OnRootLayoutAddedToViewport(ULocalPlayer* LocalPlayer, UAV_PrimaryGameLayout* Layout)
{
#if WITH_EDITOR
	if (GIsEditor && LocalPlayer->IsPrimaryPlayer())
	{
		// So our controller will work in PIE without needing to click in the viewport
		FSlateApplication::Get().SetUserFocusToGameViewport(0);
	}
#endif // WITH_EDITOR
}

void UAV_PrimaryGameLayoutSubsystem::OnRootLayoutRemovedFromViewport(ULocalPlayer* LocalPlayer, UAV_PrimaryGameLayout* Layout) { }

void UAV_PrimaryGameLayoutSubsystem::OnRootLayoutReleased(ULocalPlayer* LocalPlayer, UAV_PrimaryGameLayout* Layout) { }

void UAV_PrimaryGameLayoutSubsystem::CreateLayoutWidget(ULocalPlayer* LocalPlayer)
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

TSubclassOf<UAV_PrimaryGameLayout> UAV_PrimaryGameLayoutSubsystem::GetLayoutWidgetClass(ULocalPlayer* LocalPlayer)
{
	return LayoutClass.LoadSynchronous();
}
