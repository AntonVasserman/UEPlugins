// Copyright Anton Vasserman, All Rights Reserved.


#include "AV_SystemLibrary.h"

#include "AVUtilities.h"
#include "Kismet/KismetSystemLibrary.h"

void UAV_SystemLibrary::PrintStringExtended(const UObject* WorldContextObject, const FString& InString, bool bPrintToScreen, bool bPrintToLog, FLinearColor TextColor, float Duration, const FName Key)
{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) || USE_LOGGING_IN_SHIPPING // Do not Print in Shipping or Test unless explicitly enabled.
	UKismetSystemLibrary::PrintString(WorldContextObject, GetStringWithAppendedClass(WorldContextObject, InString), bPrintToScreen, false, TextColor, Duration, Key);
	if (bPrintToLog)
	{
		AV_LOG(Log, "%s", *GetStringWithAppendedClass(WorldContextObject, InString));
	}
#endif
}

void UAV_SystemLibrary::PrintWarningStringExtended(const UObject* WorldContextObject, const FString& InString, bool bPrintToScreen, bool bPrintToLog, float Duration, const FName Key)
{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) || USE_LOGGING_IN_SHIPPING // Do not Print in Shipping or Test unless explicitly enabled.
	UKismetSystemLibrary::PrintString(WorldContextObject, GetWarningStringWithAppendedClass(WorldContextObject, InString), bPrintToScreen, false, FColor::Yellow, Duration, Key);
	if (bPrintToLog)
	{
		AV_LOG(Warning, "%s", *GetStringWithAppendedClass(WorldContextObject, InString));
	}
#endif
}

void UAV_SystemLibrary::PrintErrorStringExtended(const UObject* WorldContextObject, const FString& InString, bool bPrintToScreen, bool bPrintToLog, float Duration, const FName Key)
{
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) || USE_LOGGING_IN_SHIPPING // Do not Print in Shipping or Test unless explicitly enabled.
	UKismetSystemLibrary::PrintString(WorldContextObject, GetErrorStringWithAppendedClass(WorldContextObject, InString), bPrintToScreen, false, FColor::Red, Duration, Key);
	if (bPrintToLog)
	{
		AV_LOG(Error, "%s", *GetStringWithAppendedClass(WorldContextObject, InString));
	}
#endif
}

FString UAV_SystemLibrary::GetStringWithAppendedClass(const UObject* WorldContext, const FString& InString)
{
	if (!WorldContext) return InString;
	
	FString ClassName = WorldContext->GetClass()->GetName();
	ClassName.RemoveFromEnd("_C");
	
	return "(" + ClassName + ") " + InString;
}

FString UAV_SystemLibrary::GetWarningStringWithAppendedClass(const UObject* WorldContext, const FString& String)
{
	return "Warning: " + GetStringWithAppendedClass(WorldContext, String);
}

FString UAV_SystemLibrary::GetErrorStringWithAppendedClass(const UObject* WorldContext, const FString& String)
{
	return "Error: " + GetStringWithAppendedClass(WorldContext, String);
}
