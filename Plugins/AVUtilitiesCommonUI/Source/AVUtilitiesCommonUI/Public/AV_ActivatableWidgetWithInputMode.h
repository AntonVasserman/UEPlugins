// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"

#include "AV_ActivatableWidgetWithInputMode.generated.h"

/**
 * Enum representing the input mode configuration for an activatable widget.
 * This determines how the input config is set when the widget is activated.
 */
UENUM(BlueprintType)
enum class EAV_InputMode : uint8
{
	Default			UMETA(DisplayName = "Default"),
	GameAndMenu		UMETA(DisplayName = "Game and Menu"),
	Game			UMETA(DisplayName = "Game Only"),
	Menu			UMETA(DisplayName = "Menu Only"),
};

/**
 * This is an activatable widget that allows to configure the desired input config to be applied when activated.
 */
UCLASS(Abstract, Blueprintable)
class AVUTILITIESCOMMONUI_API UAV_ActivatableWidgetWithInputMode : public UCommonActivatableWidget
{
	GENERATED_BODY()
protected:
	/** The desired input mode to use while this UI is activated. */
	UPROPERTY(EditDefaultsOnly, Category = Input)
	EAV_InputMode InputMode = EAV_InputMode::Default;

	/** The desired mouse behavior when the game gets input. */
	UPROPERTY(EditDefaultsOnly, Category = Input)
	EMouseCaptureMode GameMouseCaptureMode = EMouseCaptureMode::CapturePermanently;
	
	//~ UCommonActivatableWidget
public:
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
#if WITH_EDITOR
	virtual void ValidateCompiledWidgetTree(const UWidgetTree& BlueprintWidgetTree, class IWidgetCompilerLog& CompileLog) const override;
#endif // WITH_EDITOR
};
