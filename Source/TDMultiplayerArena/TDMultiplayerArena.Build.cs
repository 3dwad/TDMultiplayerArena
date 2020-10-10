// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TDMultiplayerArena : ModuleRules
{
	public TDMultiplayerArena(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicIncludePaths.AddRange(new string[]
			{
				"TDMultiplayerArena/Public/Pawn",
				"TDMultiplayerArena/Public/GameplayActors",
				"TDMultiplayerArena/Public/PawnComponents",
			}
			);
		
		PrivateIncludePaths.AddRange(new string[]
			{
				"TDMultiplayerArena/Private/Pawn",
				"TDMultiplayerArena/Private/GameplayActors",
				"TDMultiplayerArena/Private/PawnComponents",
			}
		);

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
