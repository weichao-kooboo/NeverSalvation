using UnrealBuildTool;
using Tools.DotNETCommon;
using System.IO;

public class LibuvSupport : ModuleRules
{
    public LibuvSupport(ReadOnlyTargetRules Target) : base(Target)
    {
        /*
        PublicIncludePaths.AddRange(
            new string[] {
                "LibuvSupport/"
            }
            );

        PrivateIncludePaths.AddRange(
            new string[] {
                "LibuvSupport"
            }
            );
            */
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core","CoreUObject","Engine"
        });

        RulesAssembly RA;
        FileReference CheckProjectFile;
        UProjectInfo.TryGetProjectForTarget("NeverSalvation", out CheckProjectFile);
        RA = RulesCompiler.CreateProjectRulesAssembly(CheckProjectFile);
        FileReference FR = RA.GetModuleFileName(this.GetType().Name);
        string ModulePath = Path.GetDirectoryName(FR.CanonicalName);

        string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/"));                 // gets the ThirdParty folder directory path        
        string LibuvConnectorPath = ThirdPartyPath + "libuv/";                                    // gets the Libuv Connector.C 6.1 folder path        
        string LibuvConnectorLibraryPath = LibuvConnectorPath + "lib/";                                          // gets the path of the lib folder        
        string LibuvConnectorIncludePath = LibuvConnectorPath + "include/";                                      // gets the path of the include folder        
        string LibuvConnectorImportLibraryName = Path.Combine(LibuvConnectorLibraryPath, "libuv.lib");        // gets the file path and name of the libmysql.lib static import library        
        string LibuvConnectorDLLName = Path.Combine(LibuvConnectorLibraryPath, "libuv.dll");

        if (!File.Exists(LibuvConnectorImportLibraryName))                                                       // check to ensure the static import lib can be located, or else we'll be in trouble        
        {
            throw new BuildException(string.Format("{0} could not be found.", LibuvConnectorImportLibraryName));        // log an error message explaining what went wrong if not found        
        }
        if (!File.Exists(LibuvConnectorDLLName))                                                                 // check to make sure the dll can be located or else we'll be in trouble        
        {
            throw new BuildException(string.Format("{0} could not be found.", LibuvConnectorDLLName));           // log an error message explaining what went wrong if not found        
        }
        PublicIncludePaths.Add(LibuvConnectorIncludePath);                                                       // add the "include" folder to our dependencies. I've chosen PrivateIncludePaths since I hide the mysql headers from external code        
        PublicLibraryPaths.Add(LibuvConnectorLibraryPath);                                                       // add the "lib" folder to our dependencies        
        PublicAdditionalLibraries.Add(LibuvConnectorImportLibraryName);                                          // add libmysql.lib static import library as a dependency        
        PublicDelayLoadDLLs.Add(LibuvConnectorDLLName);                                                          // add libmysql.dll as a dll    
        RuntimeDependencies.Add(new RuntimeDependency("$(ProjectDir)/Binaries/Win64/libuv.dll"));             // 自动添加libmysql.dll到指定的打包目录中
    }
    private void Trace(string msg)
    {
        Log.TraceError(msg);
    }
}