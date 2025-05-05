// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Conclave : ModuleRules
{
	public Conclave(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", 
			"UMG",
			"OnlineSubsystem", "OnlineSubsystemSteam", "OnlineSubsystemUtils" });

		PrivateIncludePaths.Add("Conclave");
		PrivateIncludePaths.Add("Conclave/Actor");
		PrivateIncludePaths.Add("Conclave/CharacterComponent");
    }
}
