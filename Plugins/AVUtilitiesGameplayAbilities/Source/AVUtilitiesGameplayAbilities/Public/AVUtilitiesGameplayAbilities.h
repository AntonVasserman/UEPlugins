// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

AVUTILITIESGAMEPLAYABILITIES_API DECLARE_LOG_CATEGORY_EXTERN(LogAV_UtilitiesGameplayAbilities, Log, All);

class FAVUtilitiesGameplayAbilitiesModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
