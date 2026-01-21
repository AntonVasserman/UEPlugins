// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "Engine/CancellableAsyncAction.h"
#include "GameplayTagContainer.h"
#include "UObject/SoftObjectPtr.h"

#include "AV_AsyncAction_PushContentToLayerAsync.generated.h"

#define UE_API AVUTILITIESCOMMONUI_API

class APlayerController;
class UCommonActivatableWidget;
class UObject;
struct FFrame;
struct FStreamableHandle;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAV_PushContentToLayerAsyncDelegate, UCommonActivatableWidget*, ActivatableWidget);

/**
 * This class provides functionality to asynchronously load and push a specified widget class
 * to a specific UI layer for a specified player using the Player Controller.
 */
UCLASS(MinimalAPI, BlueprintType)
class UAV_AsyncAction_PushContentToLayerAsync : public UCancellableAsyncAction
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Meta = (DisplayName = "Push Content To Layer Async (Player Controller)", WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UE_API UAV_AsyncAction_PushContentToLayerAsync* PushContentToLayerAsync(APlayerController* OwningPlayer, UPARAM(meta = (AllowAbstract=false)) TSoftClassPtr<UCommonActivatableWidget> ActivatableWidgetClass, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerName);

	UPROPERTY(BlueprintAssignable)
	FAV_PushContentToLayerAsyncDelegate BeforePush;

	UPROPERTY(BlueprintAssignable)
	FAV_PushContentToLayerAsyncDelegate AfterPush;

private:
	FGameplayTag LayerName;
	TWeakObjectPtr<APlayerController> OwningPlayerPtr;
	TSoftClassPtr<UCommonActivatableWidget> ActivatableWidgetClass;
	TSharedPtr<FStreamableHandle> StreamingHandle;
	
	//~ UCancellableAsyncAction
	UE_API virtual void Activate() override;
	UE_API virtual void Cancel() override;
};

#undef UE_API
