// Copyright Anton Vasserman, All Rights Reserved.


#include "Messaging/AV_CommonGameDialog.h"

#include "Messaging/AV_CommonMessagingSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AV_CommonGameDialog)

#define LOCTEXT_NAMESPACE "Messaging"

UAV_CommonGameDialogDescriptor* UAV_CommonGameDialogDescriptor::CreateConfirmationOk(const FText& Header, const FText& Body)
{
	UAV_CommonGameDialogDescriptor* Descriptor = NewObject<UAV_CommonGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FAV_ConfirmationDialogAction ConfirmAction;
	ConfirmAction.Result = EAV_CommonMessagingResult::Confirmed;
	ConfirmAction.OptionalDisplayText = LOCTEXT("Ok", "Ok");

	Descriptor->ButtonActions.Add(ConfirmAction);

	return Descriptor;
}

UAV_CommonGameDialogDescriptor* UAV_CommonGameDialogDescriptor::CreateConfirmationOkCancel(const FText& Header, const FText& Body)
{
	UAV_CommonGameDialogDescriptor* Descriptor = NewObject<UAV_CommonGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FAV_ConfirmationDialogAction ConfirmAction;
	ConfirmAction.Result = EAV_CommonMessagingResult::Confirmed;
	ConfirmAction.OptionalDisplayText = LOCTEXT("Ok", "Ok");

	FAV_ConfirmationDialogAction CancelAction;
	CancelAction.Result = EAV_CommonMessagingResult::Cancelled;
	CancelAction.OptionalDisplayText = LOCTEXT("Cancel", "Cancel");

	Descriptor->ButtonActions.Add(ConfirmAction);
	Descriptor->ButtonActions.Add(CancelAction);

	return Descriptor;
}

UAV_CommonGameDialogDescriptor* UAV_CommonGameDialogDescriptor::CreateConfirmationYesNo(const FText& Header, const FText& Body)
{
	UAV_CommonGameDialogDescriptor* Descriptor = NewObject<UAV_CommonGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FAV_ConfirmationDialogAction ConfirmAction;
	ConfirmAction.Result = EAV_CommonMessagingResult::Confirmed;
	ConfirmAction.OptionalDisplayText = LOCTEXT("Yes", "Yes");

	FAV_ConfirmationDialogAction DeclineAction;
	DeclineAction.Result = EAV_CommonMessagingResult::Declined;
	DeclineAction.OptionalDisplayText = LOCTEXT("No", "No");

	Descriptor->ButtonActions.Add(ConfirmAction);
	Descriptor->ButtonActions.Add(DeclineAction);

	return Descriptor;
}

UAV_CommonGameDialogDescriptor* UAV_CommonGameDialogDescriptor::CreateConfirmationYesNoCancel(const FText& Header, const FText& Body)
{
	UAV_CommonGameDialogDescriptor* Descriptor = NewObject<UAV_CommonGameDialogDescriptor>();
	Descriptor->Header = Header;
	Descriptor->Body = Body;

	FAV_ConfirmationDialogAction ConfirmAction;
	ConfirmAction.Result = EAV_CommonMessagingResult::Confirmed;
	ConfirmAction.OptionalDisplayText = LOCTEXT("Yes", "Yes");

	FAV_ConfirmationDialogAction DeclineAction;
	DeclineAction.Result = EAV_CommonMessagingResult::Declined;
	DeclineAction.OptionalDisplayText = LOCTEXT("No", "No");

	FAV_ConfirmationDialogAction CancelAction;
	CancelAction.Result = EAV_CommonMessagingResult::Cancelled;
	CancelAction.OptionalDisplayText = LOCTEXT("Cancel", "Cancel");

	Descriptor->ButtonActions.Add(ConfirmAction);
	Descriptor->ButtonActions.Add(DeclineAction);
	Descriptor->ButtonActions.Add(CancelAction);

	return Descriptor;
}


UAV_CommonGameDialog::UAV_CommonGameDialog()
{
}

void UAV_CommonGameDialog::SetupDialog(UAV_CommonGameDialogDescriptor* Descriptor, FAV_CommonMessagingResultDelegate ResultCallback)
{
}

void UAV_CommonGameDialog::KillDialog()
{
}

#undef LOCTEXT_NAMESPACE
