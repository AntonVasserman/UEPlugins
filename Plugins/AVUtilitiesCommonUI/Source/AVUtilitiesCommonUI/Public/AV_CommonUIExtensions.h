// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "AV_CommonUIExtensions.generated.h"

#define UE_API AVUTILITIESCOMMONUI_API

enum class ECommonInputType : uint8;

class UCommonActivatableWidget;
class UUserWidget;

/**
 * A utility class for additional functionality when working with the CommonUI plugin.
 */
UCLASS(MinimalAPI)
class  UAV_CommonUIExtensions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UAV_CommonUIExtensions() { }
	
	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Global UI Extensions", Meta = (WorldContext = "WidgetContextObject"))
	static UE_API ECommonInputType GetOwningPlayerInputType(const UUserWidget* WidgetContextObject);
	
	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Global UI Extensions", Meta = (WorldContext = "WidgetContextObject"))
	static UE_API bool IsOwningPlayerUsingGamepad(const UUserWidget* WidgetContextObject);
	
	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Global UI Extensions", Meta = (WorldContext = "WidgetContextObject"))
	static UE_API bool IsOwningPlayerUsingMouseAndKeyboard(const UUserWidget* WidgetContextObject);
	
	UFUNCTION(BlueprintPure, BlueprintCosmetic, Category = "Global UI Extensions", Meta = (WorldContext = "WidgetContextObject"))
	static UE_API bool IsOwningPlayerUsingTouch(const UUserWidget* WidgetContextObject);
};

#undef UE_API

