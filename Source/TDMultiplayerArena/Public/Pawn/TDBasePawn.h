// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "TDBasePawn.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class UTDShieldComponent;
class ATDProjectile;

UCLASS()
class TDMULTIPLAYERARENA_API ATDBasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATDBasePawn();

	UPROPERTY(VisibleAnywhere, Category="Components")
	UCapsuleComponent* BodyCapsule;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category="Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* FireLocation;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	UTDShieldComponent* ShieldComponent;

	UPROPERTY(EditAnywhere,Category="Game|Projectile" )
	TSubclassOf<ATDProjectile> ProjectileClass;

	void TurnForMouse(float InFPS);

	void Fire();
	
	UFUNCTION(Server,Reliable)
	void Fire_Server();

	UFUNCTION(Server,Unreliable)
	void TurnForMouse_Server(FRotator InRotation);

	void MoveForward(float InValue);
	void MoveRight(float InValue);

	UFUNCTION(Server,Reliable)
	void MoveForward_Server(float InValue);
	
	UFUNCTION(Server,Reliable)
	void MoveRight_Server(float InValue);

	void AllowShoot();

	UFUNCTION()
	void OnRep_Health();

	UPROPERTY(Replicated, ReplicatedUsing = OnRep_Health)
	float Health;

	UFUNCTION()
	void OnRep_IsCanFire();

	UPROPERTY(Replicated, ReplicatedUsing = OnRep_IsCanFire)
	bool bIsCanFire;

	void DealDamage(float InDamage);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FTimerHandle RateOfFire_Handle;
};
