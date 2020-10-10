// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "TDBaseUpgrade.generated.h"

class USphereComponent;

UCLASS()
class TDMULTIPLAYERARENA_API ATDBaseUpgrade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDBaseUpgrade();

	UPROPERTY(VisibleAnywhere)
	USphereComponent* BodyCollision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
