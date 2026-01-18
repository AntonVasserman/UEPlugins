// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AVUtilitiesCommonUI : ModuleRules
{
	public AVUtilitiesCommonUI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] { });
		PrivateIncludePaths.AddRange(new string[] { });
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"CommonInput",
				"CommonUI",
				"Core",
				"CoreUObject",
				"Engine",
				"GameplayTags",
				"Slate",
				"SlateCore",
				"UMG",
			});
		PrivateDependencyModuleNames.AddRange(new string[] { });
		
		DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}
