// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

AVUTILITIES_API DECLARE_LOG_CATEGORY_EXTERN(LogAV, Log, All);
#define AV_LOG(Verbosity, Format, ...) UE_LOG(LogAV, Verbosity, TEXT("%s: %s"), __FUNCTIONW__, *FString::Printf(TEXT(Format), ##__VA_ARGS__));
#define AV_LOG_EXTENDED(Verbosity, Format, ...) AV_LOG(Verbosity, "%s::%s", *(GetClass()->GetName()), *FString::Printf(TEXT(Format), ##__VA_ARGS__));

class FAVUtilitiesModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
