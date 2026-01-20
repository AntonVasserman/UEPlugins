// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "Engine/CancellableAsyncAction.h"
#include "GameplayTagContainer.h"
#include "UObject/SoftObjectPtr.h"

#include "AV_AsyncAction_PushContentToLayerForPlayerAsync.generated.h"

#define UE_API AVUTILITIESCOMMONUI_API

class APlayerController;
class UCommonActivatableWidget;
class UObject;
struct FFrame;
struct FStreamableHandle;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAV_PushContentToLayerForPlayerAsyncDelegate, UCommonActivatableWidget*, UserWidget);

/**
 * TODO
 */
UCLASS(MinimalAPI, BlueprintType)
class UAV_AsyncAction_PushContentToLayerForPlayerAsync : public UCancellableAsyncAction
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Meta = (DisplayName = "Push Content To Layer For Player Async", WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UE_API UAV_AsyncAction_PushContentToLayerForPlayerAsync* PushContentToLayerForPlayerAsync(APlayerController* OwningPlayer, UPARAM(meta = (AllowAbstract=false)) TSoftClassPtr<UCommonActivatableWidget> WidgetClass, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerName);

	UPROPERTY(BlueprintAssignable)
	FAV_PushContentToLayerForPlayerAsyncDelegate BeforePush;

	UPROPERTY(BlueprintAssignable)
	FAV_PushContentToLayerForPlayerAsyncDelegate AfterPush;

private:
	FGameplayTag LayerName;
	TWeakObjectPtr<APlayerController> OwningPlayerPtr;
	TSoftClassPtr<UCommonActivatableWidget> WidgetClass;
	TSharedPtr<FStreamableHandle> StreamingHandle;
	
	//~ UCancellableAsyncAction
	UE_API virtual void Activate() override;
	UE_API virtual void Cancel() override;
};

#undef UE_API
