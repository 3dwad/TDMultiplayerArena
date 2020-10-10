// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDShieldComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TDMULTIPLAYERARENA_API UTDShieldComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTDShieldComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void StartTimerAfterDamage();
	void ShieldRestore();
public:

	float CalculateDamage(float InDamage);

	UPROPERTY(Replicated)
	int32 MaxDurability;

	UFUNCTION()
	void OnRep_CurrentDurability();

	UPROPERTY(Replicated, ReplicatedUsing = OnRep_CurrentDurability)
	int32 CurrentDurability;

	UPROPERTY(Replicated)
	float RestoreRate;

	FTimerHandle ShieldRestore_Handle;
};
