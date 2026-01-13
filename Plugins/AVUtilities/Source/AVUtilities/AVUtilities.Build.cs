// Some copyright should be here...

using UnrealBuildTool;

public class AVUtilities : ModuleRules
{
	public AVUtilities(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[]
			{
				// ... add public include paths required here ...
			});
				
		
		PrivateIncludePaths.AddRange(
			new string[]
			{
				// ... add other private include paths required here ...
			});
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"AIModule",
				"Core",
				"GameplayStateTreeModule",
				"StateTreeModule",
			});
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			});
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			});
	}
}
