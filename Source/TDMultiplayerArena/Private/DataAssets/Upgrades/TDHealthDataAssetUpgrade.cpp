#include "TDHealthDataAssetUpgrade.h"
#include "TDCharacteristics.h"

void UTDHealthDataAssetUpgrade::MakeUpgrade(ATDBasePawn* InPawn, float InValue)
{
    if(InPawn->Characteristics->GetMaxHealth() < InValue)
    InPawn->Characteristics->SetMaxHealth(InValue);
}
