// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BasicServer : ModuleRules
{
	public BasicServer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Sockets", "Networking" });

		PublicIncludePaths.Add("$(ProjectDir)/Include");

		PublicAdditionalLibraries.Add("$(ProjectDir)/Lib/libprotobuf.lib");
	}
}
