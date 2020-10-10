// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "TDProjectile.generated.h"

class UBoxComponent;

UCLASS()
class TDMULTIPLAYERARENA_API ATDProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDProjectile();

	UPROPERTY(EditAnywhere, Category="Game|Projectile")
	float FlightSpeed;
	
	UPROPERTY(EditAnywhere, Category="Game|Projectile")
	float Damage;

	void Flight(float InFPS);

	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* BodyCollision;

	UFUNCTION()
	void CheckOverlap_OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
