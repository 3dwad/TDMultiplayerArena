#include "TDBaseUpgrade.h"
#include "TDBaseDataAssetUpgrade.h"
#include "Core/TDGameMode.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ATDBaseUpgrade::ATDBaseUpgrade()
{
	BodyCollision = CreateDefaultSubobject<USphereComponent>("BodyCollision");
	RootComponent = BodyCollision;
	BodyCollision->SetCollisionProfileName("Interactive");
	BodyCollision->SetSphereRadius(100.f);
}

void ATDBaseUpgrade::TryInteract(ATDBasePawn* InCaller)
{
	if (const auto GameMode = UGameplayStatics::GetGameMode(this))
	{
		if (const auto TDGameMode = Cast<ATDGameMode>(GameMode))
		{
			FCommonUpgrade* CurrentUpgrade = TDGameMode->Upgrades->FindRow<FCommonUpgrade>(FName(*UpgradeType.ToString()), "");
			if (CurrentUpgrade)
			{
				CurrentUpgrade->UpgradeType->MakeUpgrade(InCaller, CurrentUpgrade->Value);
				Destroy();
			}
			else
			UE_LOG(LogTemp, Error, TEXT("Row from tag %s not found"), *UpgradeType.ToString())
		}
	}
}

void ATDBaseUpgrade::BeginPlay()
{
	Super::BeginPlay();

	SetReplicates(true);
}