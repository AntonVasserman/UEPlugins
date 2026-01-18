// Copyright Anton Vasserman, All Rights Reserved.


#include "Messaging/AV_CommonMessagingSubsystem.h"

#include "Engine/GameInstance.h"
#include "Engine/LocalPlayer.h"
#include "UObject/UObjectHash.h"

bool UAV_CommonMessagingSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (const UGameInstance* GameInstance = CastChecked<ULocalPlayer>(Outer)->GetGameInstance(); 
		GameInstance && !GameInstance->IsDedicatedServerInstance())
	{
		TArray<UClass*> ChildClasses;
		GetDerivedClasses(GetClass(), ChildClasses, false);

		// Only create an instance if there is no override implementation defined elsewhere
		return ChildClasses.Num() == 0;
	}

	return false;
}

void UAV_CommonMessagingSubsystem::ShowConfirmation(UAV_CommonGameDialogDescriptor* DialogDescriptor, FAV_CommonMessagingResultDelegate ResultCallback)
{
}

void UAV_CommonMessagingSubsystem::ShowError(UAV_CommonGameDialogDescriptor* DialogDescriptor, FAV_CommonMessagingResultDelegate ResultCallback)
{
}
