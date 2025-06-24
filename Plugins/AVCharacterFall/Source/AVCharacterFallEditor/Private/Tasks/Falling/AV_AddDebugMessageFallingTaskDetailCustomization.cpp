#include "Tasks/Falling/AV_AddDebugMessageFallingTaskDetailCustomization.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "Tasks/Falling/AV_AddDebugMessageFallingTask.h"

#define LOCTEXT_NAMESPACE "FAV_AddDebugMessageFallingTaskDetailCustomization"

TSharedRef<IDetailCustomization> FAV_AddDebugMessageFallingTaskDetailCustomization::MakeInstance()
{
	return MakeShareable(new FAV_AddDebugMessageFallingTaskDetailCustomization());
}

void FAV_AddDebugMessageFallingTaskDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	// Remove/hide the original Operation property so it does not appear nested
	TSharedPtr<IPropertyHandle> OperationHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UAV_AddDebugMessageFallingTask, Operation));
	DetailBuilder.HideProperty(OperationHandle);

	// Get the inner struct's property handles
	if (OperationHandle->IsValidHandle())
	{
		uint32 NumChildren = 0;
		OperationHandle->GetNumChildren(NumChildren);

		IDetailCategoryBuilder& DefaultCategory = DetailBuilder.EditCategory("AddDebugMessage", FText::GetEmpty(), ECategoryPriority::Important);

		// Iterate over struct members
		for (uint32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex)
		{
			TSharedPtr<IPropertyHandle> ChildHandle = OperationHandle->GetChildHandle(ChildIndex);
			if (ChildHandle.IsValid() && ChildHandle->IsValidHandle())
			{
				DefaultCategory.AddProperty(ChildHandle.ToSharedRef());
			}
		}
	}
}
