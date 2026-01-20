// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "Engine/CancellableAsyncAction.h"
#include "UObject/SoftObjectPtr.h"

#include "AV_AsyncAction_CreateUserWidgetAsync.generated.h"

#define UE_API AVUTILITIES_API

class APlayerController;
class UGameInstance;
class UUserWidget;
class UWorld;
struct FFrame;
struct FStreamableHandle;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAV_CreateUserWidgetAsyncDelegate, UUserWidget*, UserWidget);

/**
 * Load the widget class asynchronously, the instance the widget after the loading completes, and return it on OnComplete.
 */
UCLASS(MinimalAPI, BlueprintType)
class UAV_AsyncAction_CreateUserWidgetAsync : public UCancellableAsyncAction
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Meta = (DisplayName = "Create User Widget Async", WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UE_API UAV_AsyncAction_CreateUserWidgetAsync* CreateUserWidgetAsync(UObject* WorldContextObject, TSoftClassPtr<UUserWidget> UserWidgetSoftClass, APlayerController* OwningPlayer);
	
	UPROPERTY(BlueprintAssignable)
	FAV_CreateUserWidgetAsyncDelegate OnComplete;

private:
	TWeakObjectPtr<APlayerController> OwningPlayer;
	TWeakObjectPtr<UWorld> World;
	TWeakObjectPtr<UGameInstance> GameInstance;
	TSoftClassPtr<UUserWidget> UserWidgetSoftClass;
	TSharedPtr<FStreamableHandle> StreamingHandle;
	
	void OnWidgetLoaded();
	
	//~ UCancellableAsyncAction
public:
	UE_API virtual void Activate() override;
	UE_API virtual void Cancel() override;
};

#undef UE_API
