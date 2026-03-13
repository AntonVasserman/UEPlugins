// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

AVUTILITIESGAMEPLAYABILITIES_API DECLARE_LOG_CATEGORY_EXTERN(LogAV_UtilitiesGameplayAbilities, Log, All);
#define AV_LOG_UTILSGAS(Verbosity, Format, ...) UE_LOG(LogAV_UtilitiesGameplayAbilities, Verbosity, TEXT("%hs: %s"), __FUNCTION__, *FString::Printf(TEXT(Format), ##__VA_ARGS__));
#define AV_LOG_UTILSGAS_EXTENDED(Verbosity, Format, ...) AV_LOG_UTILSGAS(Verbosity, "%s::%s", *(GetClass()->GetName()), *FString::Printf(TEXT(Format), ##__VA_ARGS__));

class FAVUtilitiesGameplayAbilitiesModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
