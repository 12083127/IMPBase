// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class IMPBase : ModuleRules
{
	public IMPBase(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
		
		// manually added plugins after project creation
		PublicDependencyModuleNames.AddRange(new string[] { "AIModule", "GameplayAbilities", "GameplayTags", "GameplayTasks" });
	}
}
