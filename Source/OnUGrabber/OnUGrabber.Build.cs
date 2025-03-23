// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OnUGrabber : ModuleRules
{
	public OnUGrabber(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
