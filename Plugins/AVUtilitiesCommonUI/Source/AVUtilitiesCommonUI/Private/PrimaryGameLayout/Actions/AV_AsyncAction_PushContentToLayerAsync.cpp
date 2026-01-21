// Copyright Anton Vasserman, All Rights Reserved.

#include "PrimaryGameLayout/Actions/AV_AsyncAction_PushContentToLayerAsync.h"

#include "Engine/Engine.h"
#include "PrimaryGameLayout/AV_PrimaryGameLayout.h"
#include "UObject/Stack.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AV_AsyncAction_PushContentToLayerAsync)

UAV_AsyncAction_PushContentToLayerAsync::UAV_AsyncAction_PushContentToLayerAsync(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UAV_AsyncAction_PushContentToLayerAsync* UAV_AsyncAction_PushContentToLayerAsync::PushContentToLayerAsync(APlayerController* InOwningPlayer, TSoftClassPtr<UCommonActivatableWidget> InActivatableWidgetClass, FGameplayTag InLayerName)
{
	if (InActivatableWidgetClass.IsNull())
	{
		FFrame::KismetExecutionMessage(TEXT("PushContentToLayerForPlayer was passed a null WidgetClass"), ELogVerbosity::Error);
		return nullptr;
	}

	if (UWorld* World = GEngine->GetWorldFromContextObject(InOwningPlayer, EGetWorldErrorMode::LogAndReturnNull))
	{
		UAV_AsyncAction_PushContentToLayerAsync* Action = NewObject<UAV_AsyncAction_PushContentToLayerAsync>();
		Action->ActivatableWidgetClass = InActivatableWidgetClass;
		Action->OwningPlayerPtr = InOwningPlayer;
		Action->LayerName = InLayerName;
		Action->RegisterWithGameInstance(World);

		return Action;
	}

	return nullptr;
}

//~ UCancellableAsyncAction

void UAV_AsyncAction_PushContentToLayerAsync::Activate()
{
	if (UAV_PrimaryGameLayout* RootLayout = UAV_PrimaryGameLayout::GetPrimaryGameLayout(OwningPlayerPtr.Get()))
	{
		TWeakObjectPtr WeakThis = this;
		
		StreamingHandle = RootLayout->PushWidgetToLayerAsync<UCommonActivatableWidget>(
			LayerName, 
			ActivatableWidgetClass, 
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

void UAV_AsyncAction_PushContentToLayerAsync::Cancel()
{
	Super::Cancel();

	if (StreamingHandle.IsValid())
	{
		StreamingHandle->CancelHandle();
		StreamingHandle.Reset();
	}
}

