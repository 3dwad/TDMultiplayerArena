// Fill out your copyright notice in the Description page of Project Settings.


#include "CHRoleWriter.h"

#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UCHRoleWriter::UCHRoleWriter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TextColor = FColor::Black;
	Offset = FVector(0.f, 0.f, 50.f);
	bIsEnable = true;
}


// Called when the game starts
void UCHRoleWriter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UCHRoleWriter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bIsEnable)
		WriteRole();
}

void UCHRoleWriter::WriteRole()
{
	switch (GetOwnerRole())
		{
	case ROLE_None:
		DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + Offset,"Actor: "+ GetOwner()->GetActorLabel() +". Role: None",nullptr,TextColor,0.f);
		break;
	case ROLE_SimulatedProxy:
		DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + Offset,"Actor: "+ GetOwner()->GetActorLabel() +". Role: SimulatedProxy",nullptr,TextColor,0.f);
		break;
	case ROLE_AutonomousProxy:
		DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + Offset,"Actor: "+ GetOwner()->GetActorLabel() +". Role: AutonomousProxy",nullptr,TextColor,0.f);
		break;
	case ROLE_Authority:
		DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + Offset,"Actor: "+ GetOwner()->GetActorLabel() +". Role: Authority",nullptr,TextColor,0.f);
		break;
	case ROLE_MAX:
		DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + Offset,"Actor: "+ GetOwner()->GetActorLabel() +". Role: MAX",nullptr,TextColor,0.f);
		break;
	default:
		DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + Offset,"Actor: "+ GetOwner()->GetActorLabel() +". Role: default",nullptr,TextColor,0.f);
	}
}

