#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TDAllInteractions.generated.h"

class ATDBasePawn;

UINTERFACE(MinimalAPI)
class UTDAllInteractions : public UInterface
{
    GENERATED_BODY()
};

class TDMULTIPLAYERARENA_API ITDAllInteractions
{
    GENERATED_BODY()

public:

    virtual void TryInteract(ATDBasePawn* InCaller) = 0;
};
