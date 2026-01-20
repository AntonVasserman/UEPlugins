// Some copyright should be here...

using UnrealBuildTool;

public class AVUtilities : ModuleRules
{
	public AVUtilities(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] { });
		PrivateIncludePaths.AddRange(new string[] { });
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"AIModule",
				"Core",
				"CoreUObject",
				"Engine",
				"GameplayStateTreeModule",
				"StateTreeModule",
				"Slate",
				"SlateCore",
				"UMG",
			});
		PrivateDependencyModuleNames.AddRange(new string[] { });
		
		DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}
