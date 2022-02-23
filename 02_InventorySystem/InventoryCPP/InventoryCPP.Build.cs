// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class InventoryCPP : ModuleRules
{
	public InventoryCPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "SlateCore" });
	}
}
