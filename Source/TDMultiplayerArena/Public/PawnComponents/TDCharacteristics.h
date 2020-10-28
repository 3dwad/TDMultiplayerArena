#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDCharacteristics.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TDMULTIPLAYERARENA_API UTDCharacteristics : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UTDCharacteristics();

public:
	float GetMovementSpeed() const { return MovementSpeed; }
	void SetMovementSpeed(float InValue) { MovementSpeed = InValue; }

	float GetMaxHealth() const { return MaxHealth; }
	void SetMaxHealth(float InValue) { MaxHealth = InValue; }

	float GetCurrentHealth() const { return CurrentHealth; }
	void SetCurrentHealth(float InValue) { CurrentHealth = InValue; }

	float GetRotationRate() const { return RotationRate; }

	private:

	UPROPERTY(Replicated/*, ReplicatedUsing = OnRep_MovementSpeed*/)
	float MovementSpeed;
	
	UPROPERTY(Replicated/*, ReplicatedUsing = OnRep_Health*/)
	float MaxHealth;

	UPROPERTY(Replicated/*, ReplicatedUsing = OnRep_CurrentHealth*/)
	float CurrentHealth;

	UPROPERTY()
	float RotationRate;
};