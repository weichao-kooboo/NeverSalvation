using UnrealBuildTool;

public class Logic : ModuleRules
{
    public Logic(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
                "Logic/"
            }
            );

        PrivateIncludePaths.AddRange(
            new string[] {
                "Logic"
            }
            );

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "Engine" });
    }
}