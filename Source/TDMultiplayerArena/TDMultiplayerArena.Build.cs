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
				"TDMultiplayerArena/Public/DataAssets/Upgrades",
				"TDMultiplayerArena/Public/Core"
			}
			);
		
		PrivateIncludePaths.AddRange(new string[]
			{
				"TDMultiplayerArena/Private/Pawn",
				"TDMultiplayerArena/Private/GameplayActors",
				"TDMultiplayerArena/Private/PawnComponents",
				"TDMultiplayerArena/Private/DataAssets/Upgrades",
				"TDMultiplayerArena/Private/Core"
			}
		);

		PublicDependencyModuleNames.AddRange(new string[] 
			{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"GameplayTags",
			});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
