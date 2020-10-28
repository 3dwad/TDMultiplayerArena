// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"
#include "TDGameMode.generated.h"

class UDataTable;

UCLASS()
class TDMULTIPLAYERARENA_API ATDGameMode : public AGameModeBase
{
public:

	UPROPERTY(EditAnywhere, Category="DataTables")
	UDataTable* Upgrades;

	GENERATED_BODY()
};
