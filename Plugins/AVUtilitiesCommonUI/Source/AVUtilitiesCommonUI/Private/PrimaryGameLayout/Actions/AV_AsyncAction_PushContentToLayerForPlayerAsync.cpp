// Copyright Anton Vasserman, All Rights Reserved.

#include "PrimaryGameLayout/Actions/AV_AsyncAction_PushContentToLayerForPlayerAsync.h"

#include "Engine/Engine.h"
#include "PrimaryGameLayout/AV_PrimaryGameLayout.h"
#include "UObject/Stack.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AV_AsyncAction_PushContentToLayerForPlayerAsync)

UAV_AsyncAction_PushContentToLayerForPlayerAsync::UAV_AsyncAction_PushContentToLayerForPlayerAsync(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UAV_AsyncAction_PushContentToLayerForPlayerAsync* UAV_AsyncAction_PushContentToLayerForPlayerAsync::PushContentToLayerForPlayerAsync(APlayerController* InOwningPlayer, TSoftClassPtr<UCommonActivatableWidget> InWidgetClass, FGameplayTag InLayerName)
{
	if (InWidgetClass.IsNull())
	{
		FFrame::KismetExecutionMessage(TEXT("PushContentToLayerForPlayer was passed a null WidgetClass"), ELogVerbosity::Error);
		return nullptr;
	}

	if (UWorld* World = GEngine->GetWorldFromContextObject(InOwningPlayer, EGetWorldErrorMode::LogAndReturnNull))
	{
		UAV_AsyncAction_PushContentToLayerForPlayerAsync* Action = NewObject<UAV_AsyncAction_PushContentToLayerForPlayerAsync>();
		Action->WidgetClass = InWidgetClass;
		Action->OwningPlayerPtr = InOwningPlayer;
		Action->LayerName = InLayerName;
		Action->RegisterWithGameInstance(World);

		return Action;
	}

	return nullptr;
}

//~ UCancellableAsyncAction

void UAV_AsyncAction_PushContentToLayerForPlayerAsync::Activate()
{
	if (UAV_PrimaryGameLayout* RootLayout = UAV_PrimaryGameLayout::GetPrimaryGameLayout(OwningPlayerPtr.Get()))
	{
		TWeakObjectPtr WeakThis = this;
		
		StreamingHandle = RootLayout->PushWidgetToLayerStackAsync<UCommonActivatableWidget>(
			LayerName, 
			WidgetClass, 
			[this, WeakThis](EAsyncWidgetLayerState State, UCommonActivatableWidget* Widget)
			{
				if (WeakThis.IsValid())
				{
					switch (State)
					{
						case EAsyncWidgetLayerState::Initialize:
						BeforePush.Broadcast(Widget);
						break;
					case EAsyncWidgetLayerState::AfterPush:
						AfterPush.Broadcast(Widget);
						SetReadyToDestroy();
						break;
					case EAsyncWidgetLayerState::Canceled:
						SetReadyToDestroy();
						break;
					}
				}
				SetReadyToDestroy();
			});
	}
	else
	{
		SetReadyToDestroy();
	}
}

void UAV_AsyncAction_PushContentToLayerForPlayerAsync::Cancel()
{
	Super::Cancel();

	if (StreamingHandle.IsValid())
	{
		StreamingHandle->CancelHandle();
		StreamingHandle.Reset();
	}
}

