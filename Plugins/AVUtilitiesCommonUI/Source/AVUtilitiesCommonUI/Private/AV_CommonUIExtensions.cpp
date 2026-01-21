// Copyright Anton Vasserman, All Rights Reserved.


#include "AV_CommonUIExtensions.h"

#include "CommonInputSubsystem.h"
#include "CommonInputTypeEnum.h"
#include "Engine/GameInstance.h"
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

bool UAV_CommonUIExtensions::IsOwningPlayerUsingGamepad(const UUserWidget* WidgetContextObject)
{
	return GetOwningPlayerInputType(WidgetContextObject) == ECommonInputType::Gamepad;
}

bool UAV_CommonUIExtensions::IsOwningPlayerUsingMouseAndKeyboard(const UUserWidget* WidgetContextObject)
{
	return GetOwningPlayerInputType(WidgetContextObject) == ECommonInputType::MouseAndKeyboard;
}

bool UAV_CommonUIExtensions::IsOwningPlayerUsingTouch(const UUserWidget* WidgetContextObject)
{
	return GetOwningPlayerInputType(WidgetContextObject) == ECommonInputType::Touch;
}
