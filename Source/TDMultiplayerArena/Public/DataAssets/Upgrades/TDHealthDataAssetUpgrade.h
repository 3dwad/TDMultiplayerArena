#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Upgrades/TDBaseDataAssetUpgrade.h"
#include "TDHealthDataAssetUpgrade.generated.h"

UCLASS(BlueprintType, Blueprintable)
class TDMULTIPLAYERARENA_API UTDHealthDataAssetUpgrade : public UTDBaseDataAssetUpgrade
{
	GENERATED_BODY()

	virtual void MakeUpgrade(ATDBasePawn* InPawn, float InValue) override;
};
