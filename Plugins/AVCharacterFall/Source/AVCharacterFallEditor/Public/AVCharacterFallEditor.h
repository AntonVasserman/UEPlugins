// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FAVCharacterFallEditorModule : public IModuleInterface
{
	void RegisterCustomClassLayouts();
	void UnregisterCustomClassLayouts();
	
	void SetupCustomIcons();
	void SetupCharacterFallComponentIcon(FSlateStyleSet* StyleSet);
	
	//~ IModuleInterface Begin
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	//~ IModuleInterface End
};
