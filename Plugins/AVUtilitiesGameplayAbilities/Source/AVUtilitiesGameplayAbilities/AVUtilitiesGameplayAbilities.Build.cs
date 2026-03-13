// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AVUtilitiesGameplayAbilities : ModuleRules
{
	public AVUtilitiesGameplayAbilities(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] { });
		PrivateIncludePaths.AddRange(new string[] { });
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"EnhancedInput",
				"GameplayAbilities",
				"GameplayStateTreeModule",
				"GameplayTags",
				"GameplayTasks",
				"ModelViewViewModel",
				"StateTreeModule",
				"Engine",
				"Slate",
				"SlateCore",
			});
		PrivateDependencyModuleNames.AddRange(new string[] { });
		
		DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}
