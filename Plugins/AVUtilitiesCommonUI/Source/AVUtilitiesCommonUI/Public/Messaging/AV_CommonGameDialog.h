// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CommonActivatableWidget.h"
#include "AV_CommonMessagingSubsystem.h"

#include "AV_CommonGameDialog.generated.h"

#define UE_API AVUTILITIESCOMMONUI_API

/**
 * TODO
 */
USTRUCT(BlueprintType)
struct FAV_ConfirmationDialogAction
{
	GENERATED_BODY()

	/** Required: The dialog option to provide. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	EAV_CommonMessagingResult Result = EAV_CommonMessagingResult::Unknown;

	/** Optional: Display Text to use instead of the action name associated with the result. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText OptionalDisplayText;

	bool operator==(const FAV_ConfirmationDialogAction& Other) const
	{
		return Result == Other.Result && OptionalDisplayText.EqualTo(Other.OptionalDisplayText);
	}
};

/**
 * TODO
 */
UCLASS(MinimalAPI)
class UAV_CommonGameDialogDescriptor : public UObject
{
	GENERATED_BODY()
	
public:
	static UE_API UAV_CommonGameDialogDescriptor* CreateConfirmationOk(const FText& Header, const FText& Body);
	static UE_API UAV_CommonGameDialogDescriptor* CreateConfirmationOkCancel(const FText& Header, const FText& Body);
	static UE_API UAV_CommonGameDialogDescriptor* CreateConfirmationYesNo(const FText& Header, const FText& Body);
	static UE_API UAV_CommonGameDialogDescriptor* CreateConfirmationYesNoCancel(const FText& Header, const FText& Body);

	/** The header of the message to display */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText Header;
	
	/** The body of the message to display */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FText Body;

	/** The confirm button's input action to use. */
	UPROPERTY(BlueprintReadWrite, Category = "")
	TArray<FAV_ConfirmationDialogAction> ButtonActions;
};

/**
 * TODO
 */
UCLASS(MinimalAPI, Abstract)
class UAV_CommonGameDialog : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	UE_API UAV_CommonGameDialog();
	
	UE_API virtual void SetupDialog(UAV_CommonGameDialogDescriptor* Descriptor, FAV_CommonMessagingResultDelegate ResultCallback);
	UE_API virtual void KillDialog();
};

#undef UE_API

