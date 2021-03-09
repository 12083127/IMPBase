// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class IMPBase : ModuleRules
{
	public IMPBase(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "InputCore" });
		
		// manually added plugins after project creation
		PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "GameplayAbilities", "GameplayTags", "GameplayTasks", "UMG", "Slate", "SlateCore" });
	}
}
