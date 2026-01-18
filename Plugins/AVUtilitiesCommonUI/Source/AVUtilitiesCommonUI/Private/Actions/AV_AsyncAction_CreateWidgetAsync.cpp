// Copyright Anton Vasserman, All Rights Reserved.


#include "Actions/AV_AsyncAction_CreateWidgetAsync.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Engine/AssetManager.h"
#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "UObject/Stack.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AV_AsyncAction_CreateWidgetAsync)

class UUserWidget;

UAV_AsyncAction_CreateWidgetAsync::UAV_AsyncAction_CreateWidgetAsync(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UAV_AsyncAction_CreateWidgetAsync* UAV_AsyncAction_CreateWidgetAsync::CreateWidgetAsync(UObject* InWorldContextObject, TSoftClassPtr<UUserWidget> InUserWidgetSoftClass, APlayerController* InOwningPlayer)
{
	if (InUserWidgetSoftClass.IsNull())
	{
		FFrame::KismetExecutionMessage(TEXT("CreateWidgetAsync was passed a null UserWidgetSoftClass"), ELogVerbosity::Error);
		return nullptr;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(InWorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	UAV_AsyncAction_CreateWidgetAsync* Action = NewObject<UAV_AsyncAction_CreateWidgetAsync>();
	Action->UserWidgetSoftClass = InUserWidgetSoftClass;
	Action->OwningPlayer = InOwningPlayer;
	Action->World = World;
	Action->GameInstance = World->GetGameInstance();
	Action->RegisterWithGameInstance(World);

	return Action;
}

void UAV_AsyncAction_CreateWidgetAsync::OnWidgetLoaded()
{
	// If the load is successful, create it, otherwise don't complete this.
	if (const TSubclassOf<UUserWidget> UserWidgetClass = UserWidgetSoftClass.Get())
	{
		UUserWidget* UserWidget = UWidgetBlueprintLibrary::Create(World.Get(), UserWidgetClass, OwningPlayer.Get());
		OnComplete.Broadcast(UserWidget);
	}

	StreamingHandle.Reset();
	SetReadyToDestroy();
}

//~ UCancellableAsyncAction

void UAV_AsyncAction_CreateWidgetAsync::Activate()
{
	StreamingHandle = UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		UserWidgetSoftClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateUObject(this, &ThisClass::OnWidgetLoaded),
		FStreamableManager::AsyncLoadHighPriority);
}

void UAV_AsyncAction_CreateWidgetAsync::Cancel()
{
	Super::Cancel();

	if (StreamingHandle.IsValid())
	{
		StreamingHandle->CancelHandle();
		StreamingHandle.Reset();
	}
}
