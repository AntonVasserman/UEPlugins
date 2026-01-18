// Copyright Anton Vasserman, All Rights Reserved.


#include "Actions/AV_AsyncAction_ShowConfirmation.h"

#include "Engine/GameInstance.h"
#include "Messaging/AV_CommonGameDialog.h"
#include "Messaging/AV_CommonMessagingSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AV_AsyncAction_ShowConfirmation)

UAV_AsyncAction_ShowConfirmation::UAV_AsyncAction_ShowConfirmation(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UAV_AsyncAction_ShowConfirmation* UAV_AsyncAction_ShowConfirmation::ShowConfirmationYesNo(UObject* InWorldContextObject, FText Title, FText Message)
{
	UAV_AsyncAction_ShowConfirmation* Action = NewObject<UAV_AsyncAction_ShowConfirmation>();
	Action->WorldContextObject = InWorldContextObject;
	Action->Descriptor = UAV_CommonGameDialogDescriptor::CreateConfirmationYesNo(Title, Message);
	Action->RegisterWithGameInstance(InWorldContextObject);

	return Action;
}

UAV_AsyncAction_ShowConfirmation* UAV_AsyncAction_ShowConfirmation::ShowConfirmationOkCancel(UObject* InWorldContextObject, FText Title, FText Message)
{
	UAV_AsyncAction_ShowConfirmation* Action = NewObject<UAV_AsyncAction_ShowConfirmation>();
	Action->WorldContextObject = InWorldContextObject;
	Action->Descriptor = UAV_CommonGameDialogDescriptor::CreateConfirmationOkCancel(Title, Message);
	Action->RegisterWithGameInstance(InWorldContextObject);

	return Action;
}

UAV_AsyncAction_ShowConfirmation* UAV_AsyncAction_ShowConfirmation::ShowConfirmationCustom(UObject* InWorldContextObject, UAV_CommonGameDialogDescriptor* Descriptor)
{
	UAV_AsyncAction_ShowConfirmation* Action = NewObject<UAV_AsyncAction_ShowConfirmation>();
	Action->WorldContextObject = InWorldContextObject;
	Action->Descriptor = Descriptor;
	Action->RegisterWithGameInstance(InWorldContextObject);

	return Action;
}

void UAV_AsyncAction_ShowConfirmation::HandleConfirmationResult(EAV_CommonMessagingResult ConfirmationResult)
{
	OnResult.Broadcast(ConfirmationResult);

	SetReadyToDestroy();
}

//~ UBlueprintAsyncActionBase

void UAV_AsyncAction_ShowConfirmation::Activate()
{
	if (WorldContextObject && !TargetLocalPlayer)
	{
		if (UUserWidget* UserWidget = Cast<UUserWidget>(WorldContextObject))
		{
			TargetLocalPlayer = UserWidget->GetOwningLocalPlayer<ULocalPlayer>();
		}
		else if (APlayerController* PC = Cast<APlayerController>(WorldContextObject))
		{
			TargetLocalPlayer = PC->GetLocalPlayer();
		}
		else if (UWorld* World = WorldContextObject->GetWorld())
		{
			if (UGameInstance* GameInstance = World->GetGameInstance<UGameInstance>())
			{
				TargetLocalPlayer = GameInstance->GetPrimaryPlayerController(false)->GetLocalPlayer();
			}
		}
	}

	if (TargetLocalPlayer)
	{
		if (UAV_CommonMessagingSubsystem* Messaging = TargetLocalPlayer->GetSubsystem<UAV_CommonMessagingSubsystem>())
		{
			FAV_CommonMessagingResultDelegate ResultCallback = FAV_CommonMessagingResultDelegate::CreateUObject(this, &UAV_AsyncAction_ShowConfirmation::HandleConfirmationResult);
			Messaging->ShowConfirmation(Descriptor, ResultCallback);
			return;
		}
	}
	
	// If we couldn't make the confirmation, just handle an unknown result and broadcast nothing
	HandleConfirmationResult(EAV_CommonMessagingResult::Unknown);
}
