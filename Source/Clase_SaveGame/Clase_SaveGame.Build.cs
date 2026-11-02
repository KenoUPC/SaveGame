// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Clase_SaveGame : ModuleRules
{
	public Clase_SaveGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Clase_SaveGame",
			"Clase_SaveGame/Variant_Platforming",
			"Clase_SaveGame/Variant_Platforming/Animation",
			"Clase_SaveGame/Variant_Combat",
			"Clase_SaveGame/Variant_Combat/AI",
			"Clase_SaveGame/Variant_Combat/Animation",
			"Clase_SaveGame/Variant_Combat/Gameplay",
			"Clase_SaveGame/Variant_Combat/Interfaces",
			"Clase_SaveGame/Variant_Combat/UI",
			"Clase_SaveGame/Variant_SideScrolling",
			"Clase_SaveGame/Variant_SideScrolling/AI",
			"Clase_SaveGame/Variant_SideScrolling/Gameplay",
			"Clase_SaveGame/Variant_SideScrolling/Interfaces",
			"Clase_SaveGame/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
