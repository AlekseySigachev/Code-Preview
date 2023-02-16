// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Daren : ModuleRules
{
	public Daren(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", 
	        "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "UMG", "GameplayTasks" });
    }
}
