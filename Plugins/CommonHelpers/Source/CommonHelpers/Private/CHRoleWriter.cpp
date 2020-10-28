// Fill out your copyright notice in the Description page of Project Settings.

#include "CHRoleWriter.h"

#if WITH_EDITORONLY_DATA
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#endif

// Sets default values for this component's properties
UCHRoleWriter::UCHRoleWriter()
{
	PrimaryComponentTick.bCanEverTick = true;

	RoleTextColor = FColor::Yellow;
	RemoteRoleTextColor = FColor::Black;
	RoleOffset = FVector(0.f, 0.f, 100.f);
	RemoteRoleOffset = FVector(0.f, 0.f, 50.f);
	bIsNeedRemoteRole = false;
	bIsEnable = true;
}

void UCHRoleWriter::BeginPlay()
{
	Super::BeginPlay();
}

void UCHRoleWriter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bIsEnable)
		WriteRole();
}

void UCHRoleWriter::WriteRole()
{
#if WITH_EDITOR

	switch (GetOwnerRole())
		{
	case ROLE_None:
		DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + RoleOffset,"Actor: "+ GetOwner()->GetActorLabel() +". Role: None",nullptr,RoleTextColor,0.f);
		break;
	case ROLE_SimulatedProxy:
		DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + RoleOffset,"Actor: "+ GetOwner()->GetActorLabel() +". Role: SimulatedProxy",nullptr,RoleTextColor,0.f);
		break;
	case ROLE_AutonomousProxy:
		DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + RoleOffset,"Actor: "+ GetOwner()->GetActorLabel() +". Role: AutonomousProxy",nullptr,RoleTextColor,0.f);
		break;
	case ROLE_Authority:
		DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + RoleOffset,"Actor: "+ GetOwner()->GetActorLabel() +". Role: Authority",nullptr,RoleTextColor,0.f);
		break;
	case ROLE_MAX:
		DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + RoleOffset,"Actor: "+ GetOwner()->GetActorLabel() +". Role: MAX",nullptr,RoleTextColor,0.f);
		break;
	default:
		DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + RoleOffset,"Actor: "+ GetOwner()->GetActorLabel() +". Role: default",nullptr,RoleTextColor,0.f);
	}

	if (bIsNeedRemoteRole)
	{
		switch(GetOwner()->GetRemoteRole())
		{
		case ROLE_None:
			DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + RemoteRoleOffset,"Actor: "+ GetOwner()->GetActorLabel() +". RemoteRole: None",nullptr,RemoteRoleTextColor,0.f);
			break;
		case ROLE_SimulatedProxy:
			DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + RemoteRoleOffset,"Actor: "+ GetOwner()->GetActorLabel() +". RemoteRole: SimulatedProxy",nullptr,RemoteRoleTextColor,0.f);
			break;
		case ROLE_AutonomousProxy:
			DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + RemoteRoleOffset,"Actor: "+ GetOwner()->GetActorLabel() +". RemoteRole: AutonomousProxy",nullptr,RemoteRoleTextColor,0.f);
			break;
		case ROLE_Authority:
			DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + RemoteRoleOffset,"Actor: "+ GetOwner()->GetActorLabel() +". RemoteRole: Authority",nullptr,RemoteRoleTextColor,0.f);
			break;
		case ROLE_MAX:
			DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + RemoteRoleOffset,"Actor: "+ GetOwner()->GetActorLabel() +". RemoteRole: MAX",nullptr,RemoteRoleTextColor,0.f);
			break;
		default:
			DrawDebugString(GetWorld(),GetOwner()->GetActorLocation() + RemoteRoleOffset,"Actor: "+ GetOwner()->GetActorLabel() +". RemoteRole: default",nullptr,RemoteRoleTextColor,0.f);;
		}
	}
#endif

}

