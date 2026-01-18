// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"

#include "AV_CommonMessagingSubsystem.generated.h"

#define UE_API AVUTILITIESCOMMONUI_API

class FSubsystemCollectionBase;
class UAV_CommonGameDialogDescriptor;
class UObject;

/** 
 * Possible results from a dialog 
 */
UENUM(BlueprintType)
enum class EAV_CommonMessagingResult : uint8
{
	Confirmed UMETA(DisplayName = "Confirmed", Description = "The \"yes\" button was pressed"),
	Declined UMETA(DisplayName = "Declined", Description = "The \"no\" button was pressed"),
	Cancelled UMETA(DisplayName = "Cancelled", Description = "The \"ignore/cancel\" button was pressed"),
	Killed UMETA(DisplayName = "Killed", Description = "The dialog was explicitly killed (no user input)"),
	Unknown UMETA(Hidden)
};

DECLARE_DELEGATE_OneParam(FAV_CommonMessagingResultDelegate, EAV_CommonMessagingResult /* Result */);

/**
 * TODO
 */
UCLASS(MinimalAPI, config = Game)
class UAV_CommonMessagingSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	UAV_CommonMessagingSubsystem() { }
	
	UE_API virtual void ShowConfirmation(UAV_CommonGameDialogDescriptor* DialogDescriptor, FAV_CommonMessagingResultDelegate ResultCallback = FAV_CommonMessagingResultDelegate());
	UE_API virtual void ShowError(UAV_CommonGameDialogDescriptor* DialogDescriptor, FAV_CommonMessagingResultDelegate ResultCallback = FAV_CommonMessagingResultDelegate());
	
	//~ ULocalPlayerSubsystem
public:
	UE_API virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
};

#undef UE_API
