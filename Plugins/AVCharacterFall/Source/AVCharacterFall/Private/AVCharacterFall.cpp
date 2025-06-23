// Copyright Epic Games, Inc. All Rights Reserved.

#include "AVCharacterFall.h"

#define LOCTEXT_NAMESPACE "FAVCharacterFallModule"

void FAVCharacterFallModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	// TODO: Add logic here to change FallComponent Icon
	/*
	 * references:
	 * https://www.quodsoler.com/blog/customize-your-unreal-class-icons
	 */
}

void FAVCharacterFallModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAVCharacterFallModule, AVCharacterFall)