#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "AmmoPickUpInterface.generated.h"

UINTERFACE(MinimalAPI)
class UAmmoPickUpInterface : public UInterface
{
	GENERATED_BODY()
};

class DCIH_MULTITPSGAME_API IAmmoPickUpInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddMagazine(int32 Count);
};