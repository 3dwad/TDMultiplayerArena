// Fill out your copyright notice in the Description page of Project Settings.


//#include "TDBasePawn.h"

#include "TDBasePawn.h"
#include "TDProjectile.h"
#include "TDShieldComponent.h"

#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"

const float MovementSpeed = 30.f;
const float RotationRate = 3.f;
const float RateOfFire = 1.5f;

// Sets default values
ATDBasePawn::ATDBasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 100.f;
	bIsCanFire = true;

	BodyCapsule = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	RootComponent = BodyCapsule;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	Camera->SetupAttachment(SpringArm);

	FireLocation = CreateDefaultSubobject<UArrowComponent>("FireLocation");
	FireLocation->SetupAttachment(BodyCapsule);

	ShieldComponent = CreateDefaultSubobject<UTDShieldComponent>("Shield");
}

void ATDBasePawn::TurnForMouse(float InFPS)
{
	if(!HasAuthority())
	{
		if (PlayerController)
		{
			FHitResult HitResult;
			if (PlayerController->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true,HitResult))
			{
				const auto TargetRotation = FRotator(0.f,UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HitResult.Location).Yaw,0.f);
				const FRotator CurrentRotation = UKismetMathLibrary::RLerp(GetActorRotation(),TargetRotation,RotationRate / InFPS,true);
				SetActorRotation(CurrentRotation);
				TurnForMouse_Server(CurrentRotation);
			}
		}
	}
}

void ATDBasePawn::Fire()
{
	Fire_Server();
}

void ATDBasePawn::Fire_Server_Implementation()
{
	if(ProjectileClass && bIsCanFire)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ATDProjectile>(ProjectileClass,FireLocation->GetComponentLocation(),GetActorRotation(),SpawnParams);
		
		bIsCanFire = false;
		GetWorld()->GetTimerManager().SetTimer(RateOfFire_Handle, this, &ATDBasePawn::AllowShoot,RateOfFire,false);
	}
}

void ATDBasePawn::TurnForMouse_Server_Implementation(FRotator InRotation)
{
	SetActorRotation(InRotation);
}

void ATDBasePawn::MoveForward(float InValue)
{
	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		MoveForward_Server(InValue);
		AddActorWorldOffset(FVector::ForwardVector * InValue * MovementSpeed, true);
	}
}

void ATDBasePawn::MoveRight(float InValue)
{
	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		MoveRight_Server(InValue);
		AddActorWorldOffset(FVector::RightVector * InValue * MovementSpeed, true);
	}
}

void ATDBasePawn::MoveForward_Server_Implementation(float InValue)
{
	AddActorWorldOffset(FVector::ForwardVector * InValue * MovementSpeed,true);
}

void ATDBasePawn::MoveRight_Server_Implementation(float InValue)
{
	AddActorWorldOffset(FVector::RightVector * InValue * MovementSpeed,true);
}

void ATDBasePawn::AllowShoot()
{
	bIsCanFire = true;
}

void ATDBasePawn::OnRep_Health()
{
	if(IsLocallyControlled())
	DrawDebugString(GetWorld(), GetActorLocation(), "HealthChange!", nullptr, FColor::Red, 5.f, true,2);
}

void ATDBasePawn::OnRep_IsCanFire()
{
	if(bIsCanFire && IsLocallyControlled())
	DrawDebugString(GetWorld(), GetActorLocation() + FVector(0.f,0.f,300.f), "CanFire!", nullptr, FColor::Green, 2.f,true,2);
}

void ATDBasePawn::DealDamage(float InDamage)
{
	const float DamageAfterShield  = ShieldComponent->CalculateDamage(InDamage);
	if (DamageAfterShield > 0.f)
	{
		DamageAfterShield < Health ? Health -= DamageAfterShield : Health = 0.f;

		if (Health == 0.f)
			Destroy();
	}
}

// Called when the game starts or when spawned
void ATDBasePawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController> (GetController());
}

// Called every frame
void ATDBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float FPS = 1 / DeltaTime;
	TurnForMouse(FPS);
	DrawDebugString(GetWorld(), GetActorLocation() + FVector(0.f,0.f,220.f), "Health:" + FString::SanitizeFloat(Health), nullptr, FColor::Green, 0.f,true,2);
	DrawDebugString(GetWorld(), GetActorLocation() + FVector(0.f,0.f,150.f),
		"Shield:" + FString::SanitizeFloat(ShieldComponent->CurrentDurability) + "/" + FString::SanitizeFloat(ShieldComponent->MaxDurability),
		nullptr, FColor::Blue, 0.f,true,2);
}

// Called to bind functionality to input
void ATDBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATDBasePawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATDBasePawn::MoveRight);
	PlayerInputComponent->BindAction("Fire",EInputEvent::IE_Pressed,this,&ATDBasePawn::Fire);
}

void ATDBasePawn::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATDBasePawn, Health);
	DOREPLIFETIME(ATDBasePawn, bIsCanFire);
}

