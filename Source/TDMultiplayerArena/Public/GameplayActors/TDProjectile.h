// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "TDProjectile.generated.h"

class UBoxComponent;
class UDestructibleComponent;

UCLASS()
class TDMULTIPLAYERARENA_API ATDProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ATDProjectile();

	UPROPERTY(EditAnywhere, Category="Game|Projectile")
	float FlightSpeed;
	
	UPROPERTY(EditAnywhere, Category="Game|Projectile")
	float Damage;

	void Flight(float InFPS);

	UFUNCTION(NetMulticast, Reliable)
	void BlowUp(UDestructibleComponent* InComponent);

	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* BodyCollision;

	UFUNCTION()
	void CheckOverlap_OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
