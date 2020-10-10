// Fill out your copyright notice in the Description page of Project Settings.

#include "TDProjectile.h"

#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "TDBasePawn.h"

const FVector ProjectileSize = FVector(30.f,5.f,5.f);

// Sets default values
ATDProjectile::ATDProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FlightSpeed = 250.f;
	Damage = 10.f;
	
	SetReplicates(true);
	SetReplicatingMovement(true);
	
	BodyCollision = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BodyCollision->SetBoxExtent(ProjectileSize);
	RootComponent = BodyCollision;
}

void ATDProjectile::Flight(float InFPS)
{
	FVector Speed = GetActorForwardVector() * FlightSpeed / InFPS;
	AddActorWorldOffset(Speed,true);
}

void ATDProjectile::CheckOverlap_OnComponentBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (auto OverlappedTDPawn = Cast<ATDBasePawn>(OtherActor))
	{
		if (OverlappedTDPawn != GetInstigator())
		{
			if (!HasAuthority())
			{
				if(GetInstigator()->GetLocalRole() == ROLE_AutonomousProxy)
					DrawDebugString(GetWorld(), GetActorLocation() + FVector(0.f,0.f,200.f), "Confirmation of damage!", nullptr, FColor::Red, 2.f, true, 2);
			}

			if(HasAuthority())
			{
				DrawDebugString(GetWorld(), GetActorLocation(), "HIT!", nullptr, FColor::Red, 5.f);
				OverlappedTDPawn->DealDamage(Damage);
				Destroy();
			}
		}
	}
}

// Called when the game starts or when spawned
void ATDProjectile::BeginPlay()
{
	Super::BeginPlay();
	BodyCollision->OnComponentBeginOverlap.AddDynamic(this, &ATDProjectile::CheckOverlap_OnComponentBeginOverlap);
}

// Called every frame
void ATDProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float FPS = 1 / DeltaTime;
	
	Flight(FPS);

	DrawDebugString(GetWorld(), GetActorLocation() + FVector(0.f,0.f,100.f), "Damage:" + FString::SanitizeFloat(Damage), nullptr, FColor::Red, 0.f,true,2);
}

