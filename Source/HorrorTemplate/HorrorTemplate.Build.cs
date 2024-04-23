// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HorrorTemplate : ModuleRules
{
	public HorrorTemplate(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayTags", "GameplayDebugger" });
	}
}
