// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "AV_SystemLibrary.generated.h"

UCLASS(MinimalAPI)
class UAV_SystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Development", Meta = (DevelopmentOnly, DisplayName = "Print String (Extended)", Keywords = "log print", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AdvancedDisplay = "2"))
	static AVUTILITIES_API void PrintStringExtended(const UObject* WorldContextObject, const FString& InString = FString(TEXT("Hello")), bool bPrintToScreen = true, bool bPrintToLog = true, FLinearColor TextColor = FLinearColor(0.0f, 0.66f, 1.0f), float Duration = 2.f, const FName Key = NAME_None);
	
	UFUNCTION(BlueprintCallable, Category = "Development", Meta = (DevelopmentOnly, DisplayName = "Print Warning String (Extended)", Keywords = "warning print", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AdvancedDisplay = "2"))
	static AVUTILITIES_API void PrintWarningStringExtended(const UObject* WorldContextObject, const FString& InString = FString(TEXT("Hello")), bool bPrintToScreen = true, bool bPrintToLog = true, float Duration = 2.f, const FName Key = NAME_None);
	
	UFUNCTION(BlueprintCallable, Category = "Development", Meta = (DevelopmentOnly, DisplayName = "Print Error String (Extended)", Keywords = "error print", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AdvancedDisplay = "2"))
	static AVUTILITIES_API void PrintErrorStringExtended(const UObject* WorldContextObject, const FString& InString = FString(TEXT("Hello")), bool bPrintToScreen = true, bool bPrintToLog = true, float Duration = 2.f, const FName Key = NAME_None);
	
private:
	static FString GetStringWithAppendedClass(const UObject* WorldContext, const FString& String);
	static FString GetWarningStringWithAppendedClass(const UObject* WorldContext, const FString& String);
	static FString GetErrorStringWithAppendedClass(const UObject* WorldContext, const FString& String);
};
