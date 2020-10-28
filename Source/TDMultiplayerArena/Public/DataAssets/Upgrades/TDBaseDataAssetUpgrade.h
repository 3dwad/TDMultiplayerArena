#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDBasePawn.h"
#include "Engine/DataTable.h"

#include "TDBaseDataAssetUpgrade.generated.h"

UCLASS(BlueprintType, Blueprintable)
class TDMULTIPLAYERARENA_API UTDBaseDataAssetUpgrade : public UDataAsset
{
public:

	virtual void MakeUpgrade(ATDBasePawn* InPawn, float InValue){}

protected:

	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FCommonUpgrade : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTDBaseDataAssetUpgrade* UpgradeType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
};
