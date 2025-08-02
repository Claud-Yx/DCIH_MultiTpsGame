// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DCIH_MultiTpsGame : ModuleRules
{
	public DCIH_MultiTpsGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] { 
			"DCIH_MultiTpsGame", 
			"DCIH_MultiTpsGame/Game" 
		});

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
