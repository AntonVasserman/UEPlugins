using UnrealBuildTool;

public class AVUtilitiesEditor : ModuleRules
{
    public AVUtilitiesEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Blutility",
                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UMG",
            }
        );
        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}