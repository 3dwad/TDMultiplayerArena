// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CHRoleWriter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMMONHELPERS_API UCHRoleWriter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCHRoleWriter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void WriteRole();

	UPROPERTY(EditAnywhere, Category="RoleWriter")
	FColor RoleTextColor;

	UPROPERTY(EditAnywhere, Category="RoleWriter")
	FColor RemoteRoleTextColor;

	UPROPERTY(EditAnywhere, Category="RoleWriter")
	FVector RoleOffset;

	UPROPERTY(EditAnywhere, Category="RoleWriter")
	FVector RemoteRoleOffset;

	UPROPERTY(EditAnywhere, Category="RoleWriter")
	bool bIsNeedRemoteRole;

	UPROPERTY(EditAnywhere, Category="RoleWriter")
	bool bIsEnable;
};
