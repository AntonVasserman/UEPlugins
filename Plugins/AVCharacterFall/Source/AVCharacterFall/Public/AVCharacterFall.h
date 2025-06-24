// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FAVCharacterFallModule : public IModuleInterface
{
#if WITH_EDITOR
	void SetupCustomIcons();
	void SetupCharacterFallComponentIcon(FSlateStyleSet* StyleSet);
#endif
	
	//~ IModuleInterface Begin
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//~ IModuleInterface End
};
