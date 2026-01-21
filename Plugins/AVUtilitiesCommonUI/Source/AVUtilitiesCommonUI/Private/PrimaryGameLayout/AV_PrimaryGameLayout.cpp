// Copyright Anton Vasserman, All Rights Reserved.


#include "PrimaryGameLayout/AV_PrimaryGameLayout.h"

#include "Engine/GameInstance.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "PrimaryGameLayout/AV_PrimaryGameLayoutSubsystem.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AV_PrimaryGameLayout)

/*static*/ UAV_PrimaryGameLayout* UAV_PrimaryGameLayout::GetPrimaryGameLayoutForPrimaryPlayer(const UObject* WorldContextObject)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject);
	APlayerController* PlayerController = GameInstance->GetPrimaryPlayerController(false);
	return GetPrimaryGameLayout(PlayerController);
}

/*static*/ UAV_PrimaryGameLayout* UAV_PrimaryGameLayout::GetPrimaryGameLayout(APlayerController* PlayerController)
{
	return PlayerController ? GetPrimaryGameLayout(Cast<ULocalPlayer>(PlayerController->Player)) : nullptr;
}

/*static*/ UAV_PrimaryGameLayout* UAV_PrimaryGameLayout::GetPrimaryGameLayout(ULocalPlayer* LocalPlayer)
{
	if (LocalPlayer)
	{
		const ULocalPlayer* CommonLocalPlayer = CastChecked<ULocalPlayer>(LocalPlayer);
		if (const UGameInstance* GameInstance = CommonLocalPlayer->GetGameInstance())
		{
			if (UAV_PrimaryGameLayoutSubsystem* UIManager = GameInstance->GetSubsystem<UAV_PrimaryGameLayoutSubsystem>())
			{
				if (UAV_PrimaryGameLayout* RootLayout = UIManager->GetRootLayout(CommonLocalPlayer))
				{
					return RootLayout;
				}
			}
		}
	}

	return nullptr;
}

UAV_PrimaryGameLayout::UAV_PrimaryGameLayout(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UAV_PrimaryGameLayout::RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget)
{
	if (!IsDesignTime())
	{
		LayerWidget->SetTransitionDuration(0.0);

		Layers.Add(LayerTag, LayerWidget);
	}
}

void UAV_PrimaryGameLayout::FindAndRemoveWidgetFromLayers(UCommonActivatableWidget* ActivatableWidget)
{
	// We're not sure what layer the widget is in, so we search.
	for (const auto& LayerKVP : Layers)
	{
		LayerKVP.Value->RemoveWidget(*ActivatableWidget);
	}
}

UCommonActivatableWidgetContainerBase* UAV_PrimaryGameLayout::GetLayerWidget(FGameplayTag LayerName) const
{
	return Layers.FindRef(LayerName);
}
