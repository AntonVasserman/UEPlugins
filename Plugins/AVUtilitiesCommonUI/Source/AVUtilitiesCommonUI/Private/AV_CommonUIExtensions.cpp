// Copyright Anton Vasserman, All Rights Reserved.


#include "AV_CommonUIExtensions.h"

#include "CommonInputSubsystem.h"
#include "CommonInputTypeEnum.h"
#include "Engine/GameInstance.h"
#include "PrimaryGameLayout/AV_PrimaryGameLayout.h"
#include "PrimaryGameLayout/AV_PrimaryGameLayoutSubsystem.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AV_CommonUIExtensions)

ECommonInputType UAV_CommonUIExtensions::GetOwningPlayerInputType(const UUserWidget* WidgetContextObject)
{
	if (WidgetContextObject)
	{
		if (const UCommonInputSubsystem* InputSubsystem = UCommonInputSubsystem::Get(WidgetContextObject->GetOwningLocalPlayer()))
		{
			return InputSubsystem->GetCurrentInputType();
		}
	}

	return ECommonInputType::Count;
}

bool UAV_CommonUIExtensions::IsOwningPlayerUsingTouch(const UUserWidget* WidgetContextObject)
{
	if (WidgetContextObject)
	{
		if (const UCommonInputSubsystem* InputSubsystem = UCommonInputSubsystem::Get(WidgetContextObject->GetOwningLocalPlayer()))
		{
			return InputSubsystem->GetCurrentInputType() == ECommonInputType::Touch;
		}
	}
	
	return false;
}

bool UAV_CommonUIExtensions::IsOwningPlayerUsingGamepad(const UUserWidget* WidgetContextObject)
{
	if (WidgetContextObject)
	{
		if (const UCommonInputSubsystem* InputSubsystem = UCommonInputSubsystem::Get(WidgetContextObject->GetOwningLocalPlayer()))
		{
			return InputSubsystem->GetCurrentInputType() == ECommonInputType::Gamepad;
		}
	}
	
	return false;
}

UCommonActivatableWidget* UAV_CommonUIExtensions::PushContentToLayer_ForPlayer(const ULocalPlayer* LocalPlayer, FGameplayTag LayerName, TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	if (!ensure(LocalPlayer) || !ensure(WidgetClass != nullptr))
	{
		return nullptr;
	}

	if (UAV_PrimaryGameLayoutSubsystem* UIManager = LocalPlayer->GetGameInstance()->GetSubsystem<UAV_PrimaryGameLayoutSubsystem>())
	{
		if (UAV_PrimaryGameLayout* RootLayout = UIManager->GetRootLayout(CastChecked<ULocalPlayer>(LocalPlayer)))
		{
			return RootLayout->PushWidgetToLayerStack(LayerName, WidgetClass);
		}
	}

	return nullptr;
}

void UAV_CommonUIExtensions::PushStreamedContentToLayer_ForPlayer(const ULocalPlayer* LocalPlayer, FGameplayTag LayerName, TSoftClassPtr<UCommonActivatableWidget> WidgetClass)
{
	if (!ensure(LocalPlayer) || !ensure(!WidgetClass.IsNull()))
	{
		return;
	}

	if (UAV_PrimaryGameLayoutSubsystem* UIManager = LocalPlayer->GetGameInstance()->GetSubsystem<UAV_PrimaryGameLayoutSubsystem>())
	{
		if (UAV_PrimaryGameLayout* RootLayout = UIManager->GetRootLayout(CastChecked<ULocalPlayer>(LocalPlayer)))
		{
			RootLayout->PushWidgetToLayerStackAsync(LayerName, WidgetClass);
		}
	}
}

void UAV_CommonUIExtensions::PopContentFromLayer(UCommonActivatableWidget* ActivatableWidget)
{
	if (!ActivatableWidget)
	{
		// Ignore request to pop an already deleted widget
		return;
	}

	if (const ULocalPlayer* LocalPlayer = ActivatableWidget->GetOwningLocalPlayer())
	{
		if (const UAV_PrimaryGameLayoutSubsystem* UIManager = LocalPlayer->GetGameInstance()->GetSubsystem<UAV_PrimaryGameLayoutSubsystem>())
		{
			if (UAV_PrimaryGameLayout* RootLayout = UIManager->GetRootLayout(CastChecked<ULocalPlayer>(LocalPlayer)))
			{
				RootLayout->FindAndRemoveWidgetFromLayer(ActivatableWidget);
			}
		}
	}
}
