// Copyright Epic Games, Inc. All Rights Reserved.

#include "AVCharacterFall.h"

#include "Components/AV_CharacterFallComponent.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/AppStyle.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateTypes.h"

#define LOCTEXT_NAMESPACE "FAVCharacterFallModule"

#define SLATE_IMAGE_BRUSH(ImagePath, ImageSize) new FSlateImageBrush(StyleSet->RootToContentDir(TEXT(ImagePath), TEXT(".png")), FVector2D(ImageSize, ImageSize))

#if WITH_EDITOR
void FAVCharacterFallModule::SetupCustomIcons()
{
	static TSharedPtr<FSlateStyleSet> StyleSet = nullptr;
	
	if (!StyleSet.IsValid())
	{
		// Setup StyleSet
		StyleSet = MakeShareable(new FSlateStyleSet("AVCharacterFallStyle"));
		if (const TSharedPtr<IPlugin> CurrentPlugin = IPluginManager::Get().FindPlugin(TEXT("AVCharacterFall"));
			CurrentPlugin.IsValid())
		{
			const FString ContentDir = CurrentPlugin->GetContentDir();
			StyleSet->SetContentRoot(ContentDir / TEXT("Editor/Slate"));
		}

		// Setup-ups
		SetupCharacterFallComponentIcon(StyleSet.Get());
		
		FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
	}
}

void FAVCharacterFallModule::SetupCharacterFallComponentIcon(FSlateStyleSet* StyleSet)
{
	// Old example code to setup the Icon to the CharacterMovementComponent Icon:
	/*
	if (const FSlateBrush* EngineCMCBrush = FAppStyle::Get().GetBrush(TEXT("ClassIcon.CharacterMovementComponent"));
			EngineCMCBrush != nullptr)
	{
		StyleSet->Set(
			*FString::Printf(TEXT("ClassIcon.%s"), *UAV_CharacterFallComponent::StaticClass()->GetName()),
			new FSlateBrush(*EngineCMCBrush));   // Make a copy so it isn't a const.

	}
	*/

	const FString CFCIconPropName = FString::Printf(TEXT("ClassIcon.%s"), *UAV_CharacterFallComponent::StaticClass()->GetName());
	const FString CFCIconPath = FString::Printf(TEXT("/Icons/%sClassIcon"), *UAV_CharacterFallComponent::StaticClass()->GetName());
	FSlateImageBrush* CFCIconBrush = new FSlateImageBrush(StyleSet->RootToContentDir(CFCIconPath, TEXT(".png")), FVector2D(20.f, 20.f));

	StyleSet->Set(*CFCIconPropName, CFCIconBrush);
}
#endif

//~ IModuleInterface Begin

void FAVCharacterFallModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
#if WITH_EDITOR
	SetupCustomIcons();
#endif
}

void FAVCharacterFallModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

//~ IModuleInterface End

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAVCharacterFallModule, AVCharacterFall)