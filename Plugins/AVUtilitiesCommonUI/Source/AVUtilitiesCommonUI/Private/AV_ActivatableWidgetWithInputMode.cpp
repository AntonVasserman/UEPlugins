// Copyright Anton Vasserman, All Rights Reserved.


#include "AV_ActivatableWidgetWithInputMode.h"

#include "Editor/WidgetCompilerLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AV_ActivatableWidgetWithInputMode)

//~ UCommonActivatableWidget

TOptional<FUIInputConfig> UAV_ActivatableWidgetWithInputMode::GetDesiredInputConfig() const
{
	switch (InputMode)
	{
	case EAV_InputMode::GameAndMenu:
		return FUIInputConfig(ECommonInputMode::All, GameMouseCaptureMode);
	case EAV_InputMode::Game:
		return FUIInputConfig(ECommonInputMode::Game, GameMouseCaptureMode);
	case EAV_InputMode::Menu:
		return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
	case EAV_InputMode::Default:
	default:
		return TOptional<FUIInputConfig>();
	}
}

#if WITH_EDITOR

void UAV_ActivatableWidgetWithInputMode::ValidateCompiledWidgetTree(const UWidgetTree& BlueprintWidgetTree, IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledWidgetTree(BlueprintWidgetTree, CompileLog);

	if (!GetClass()->IsFunctionImplementedInScript(GET_FUNCTION_NAME_CHECKED(ThisClass, BP_GetDesiredFocusTarget)))
	{
		CompileLog.Warning(FText::FromString(TEXT("GetDesiredFocusTarget wasn't implemented, you're going to have trouble using gamepads on this screen.")));
	}
}

#endif // WITH_EDITOR