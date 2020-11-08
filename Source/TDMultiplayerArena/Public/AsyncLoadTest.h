// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
//#include "UObject/ObjectMacros.h"

#include "AsyncLoadTest.generated.h"

UCLASS(Blueprintable)
class TDMULTIPLAYERARENA_API UAsyncLoadTest : public UObject
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UStaticMesh>> TestingMeshes;



	UFUNCTION(BlueprintCallable)
	void TryAsyncLoad();

	void OnAssetLoad();
	
};
