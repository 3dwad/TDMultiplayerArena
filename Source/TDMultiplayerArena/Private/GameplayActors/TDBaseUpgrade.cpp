// Fill out your copyright notice in the Description page of Project Settings.

#include "TDBaseUpgrade.h"

#include "Components/SphereComponent.h"


// Sets default values
ATDBaseUpgrade::ATDBaseUpgrade()
{
	BodyCollision = CreateDefaultSubobject<USphereComponent>("BodyCollision");
	RootComponent = BodyCollision;
	BodyCollision->SetCollisionProfileName("Interactive");
	BodyCollision->SetSphereRadius(100.f);
}

// Called when the game starts or when spawned
void ATDBaseUpgrade::BeginPlay()
{
	Super::BeginPlay();
}