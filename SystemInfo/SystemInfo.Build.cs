using UnrealBuildTool;

public class SystemInfo : ModuleRules
{
    public SystemInfo(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core","CoreUObject","Engine"
        });
    }
}