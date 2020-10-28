#include "TDCharacteristics.h"

#include "Net/UnrealNetwork.h"

void UTDCharacteristics::BeginPlay()
{
	Super::BeginPlay();
	SetIsReplicated(true);
}

UTDCharacteristics::UTDCharacteristics()
{
	MovementSpeed = 30.f;
	MaxHealth = 100.f;
	CurrentHealth = MaxHealth;
	RotationRate = 3.0f;
}

void UTDCharacteristics::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTDCharacteristics, MovementSpeed);
	DOREPLIFETIME(UTDCharacteristics, MaxHealth);
	DOREPLIFETIME(UTDCharacteristics, CurrentHealth);
}
