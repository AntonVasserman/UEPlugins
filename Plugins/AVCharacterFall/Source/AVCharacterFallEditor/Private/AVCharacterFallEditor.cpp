// Copyright Epic Games, Inc. All Rights Reserved.

#include "AVCharacterFallEditor/Public/AVCharacterFallEditor.h"

#include "Components/AV_CharacterFallComponent.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/AppStyle.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateTypes.h"
#include "Tasks/Falling/AV_AddDebugMessageFallingTask.h"
#include "Tasks/Falling/AV_AddDebugMessageFallingTaskDetailCustomization.h"

#define LOCTEXT_NAMESPACE "FAVCharacterFallModule"

void FAVCharacterFallEditorModule::RegisterCustomClassLayouts()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	UE_LOG(LogAV_CharacterFall, Display, TEXT("Register: %s"), *UAV_AddDebugMessageFallingTask::StaticClass()->GetName())
	PropertyModule.RegisterCustomClassLayout(
		*UAV_AddDebugMessageFallingTask::StaticClass()->GetName(),
		FOnGetDetailCustomizationInstance::CreateStatic(&FAV_AddDebugMessageFallingTaskDetailCustomization::MakeInstance)
	);
}

void FAVCharacterFallEditorModule::UnregisterCustomClassLayouts()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomClassLayout(*UAV_AddDebugMessageFallingTask::StaticClass()->GetName());
	UE_LOG(LogAV_CharacterFall, Display, TEXT("Unregister: %s"), *UAV_AddDebugMessageFallingTask::StaticClass()->GetName())
}

void FAVCharacterFallEditorModule::SetupCustomIcons()
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

void FAVCharacterFallEditorModule::SetupCharacterFallComponentIcon(FSlateStyleSet* StyleSet)
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

//~ IModuleInterface Begin

void FAVCharacterFallEditorModule::StartupModule()
{
	RegisterCustomClassLayouts();
	SetupCustomIcons();
}

void FAVCharacterFallEditorModule::ShutdownModule()
{
	UnregisterCustomClassLayouts();
}

//~ IModuleInterface End

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAVCharacterFallEditorModule, AVCharacterFallEditor)
