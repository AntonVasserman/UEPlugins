using UnrealBuildTool;

public class AVUtilitiesGameplayAbilitiesEditor : ModuleRules
{
    public AVUtilitiesGameplayAbilitiesEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore"
            }
        );
        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}