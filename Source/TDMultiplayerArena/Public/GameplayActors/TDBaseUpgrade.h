#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TDAllInteractions.h"
#include "TDBaseUpgrade.generated.h"

class USphereComponent;
class UTDBaseDataAssetUpgrade;

UCLASS()
class TDMULTIPLAYERARENA_API ATDBaseUpgrade : public AActor, public ITDAllInteractions
{
	GENERATED_BODY()

public:
	ATDBaseUpgrade();

	UPROPERTY(VisibleAnywhere)
	USphereComponent* BodyCollision;

	UPROPERTY(EditAnywhere, Category="UpgradeSettings")
	FGameplayTag UpgradeType;

	//	ITDAllInteractions interface
	virtual void TryInteract(ATDBasePawn* InCaller) override;

protected:
	virtual void BeginPlay() override;
};
