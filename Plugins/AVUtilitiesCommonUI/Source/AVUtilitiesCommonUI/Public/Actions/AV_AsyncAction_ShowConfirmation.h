// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "Kismet/BlueprintAsyncActionBase.h"
#include "UObject/ObjectPtr.h"

#include "AV_AsyncAction_ShowConfirmation.generated.h"

enum class EAV_CommonMessagingResult : uint8;

class FText;
class UAV_CommonGameDialogDescriptor;
class ULocalPlayer;
struct FFrame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAV_CommonMessagingResultMCDelegate, EAV_CommonMessagingResult, Result);

/**
 * Allows easily triggering an async confirmation dialog in blueprints that you can then wait on the result.
 */
UCLASS()
class UAV_AsyncAction_ShowConfirmation : public UBlueprintAsyncActionBase
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (BlueprintInternalUseOnly = "true", WorldContext = "InWorldContextObject"))
	static UAV_AsyncAction_ShowConfirmation* ShowConfirmationYesNo(UObject* InWorldContextObject, FText Title, FText Message);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (BlueprintInternalUseOnly = "true", WorldContext = "InWorldContextObject"))
	static UAV_AsyncAction_ShowConfirmation* ShowConfirmationOkCancel(UObject* InWorldContextObject, FText Title, FText Message);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (BlueprintInternalUseOnly = "true", WorldContext = "InWorldContextObject"))
	static UAV_AsyncAction_ShowConfirmation* ShowConfirmationCustom(UObject* InWorldContextObject, UAV_CommonGameDialogDescriptor* Descriptor);

	UPROPERTY(BlueprintAssignable)
	FAV_CommonMessagingResultMCDelegate OnResult;

private:
	UPROPERTY(Transient)
	TObjectPtr<UObject> WorldContextObject;

	UPROPERTY(Transient)
	TObjectPtr<ULocalPlayer> TargetLocalPlayer;

	UPROPERTY(Transient)
	TObjectPtr<UAV_CommonGameDialogDescriptor> Descriptor;
	
	void HandleConfirmationResult(EAV_CommonMessagingResult ConfirmationResult);
	
	//~ UBlueprintAsyncActionBase
	virtual void Activate() override;
};
