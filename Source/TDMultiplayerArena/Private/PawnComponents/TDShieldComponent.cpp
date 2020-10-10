// Fill out your copyright notice in the Description page of Project Settings.

#include "TDShieldComponent.h"

#include "DrawDebugHelpers.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UTDShieldComponent::UTDShieldComponent()
{
	MaxDurability = 30;
	RestoreRate = 0.5f;
	CurrentDurability = MaxDurability;
}

// Called when the game starts
void UTDShieldComponent::BeginPlay()
{
	Super::BeginPlay();
	SetIsReplicated(true);
}

void UTDShieldComponent::StartTimerAfterDamage()
{
	FTimerManager& TM = GetWorld()->GetTimerManager();

	if (TM.IsTimerActive(ShieldRestore_Handle))
		TM.ClearTimer(ShieldRestore_Handle);

	TM.SetTimer(ShieldRestore_Handle, this, &UTDShieldComponent::ShieldRestore, RestoreRate, true, 3.f);
}

void UTDShieldComponent::ShieldRestore()
{
	if (CurrentDurability >= MaxDurability)
	{
		GetWorld()->GetTimerManager().ClearTimer(ShieldRestore_Handle);
		return;
	}

	// Increase on 5%
	CurrentDurability += MaxDurability * 0.05f;
}

float UTDShieldComponent::CalculateDamage(float InDamage)
{
	StartTimerAfterDamage();

	if (CurrentDurability == 0)
		return InDamage;

	if (InDamage <= CurrentDurability)
	{
		CurrentDurability -= InDamage;
		return 0.f;
	}

	{
		const float DamageAfterShield = CurrentDurability - InDamage;
		CurrentDurability = 0;
		return DamageAfterShield * -1;
	}
}

void UTDShieldComponent::OnRep_CurrentDurability()
{
	if (GetOwnerRole() == ROLE_AutonomousProxy && CurrentDurability >= MaxDurability)
	 	DrawDebugString(GetWorld(), GetOwner()->GetActorLocation(), "Shield max", nullptr, FColor::Blue, 5.f, true, 2);
}

void UTDShieldComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTDShieldComponent, MaxDurability);
	DOREPLIFETIME(UTDShieldComponent, CurrentDurability);
	DOREPLIFETIME(UTDShieldComponent, RestoreRate);
}
