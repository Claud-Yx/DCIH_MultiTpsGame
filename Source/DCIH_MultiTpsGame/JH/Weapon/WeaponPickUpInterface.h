#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "WeaponPickUpInterface.generated.h"

UINTERFACE(MinimalAPI)
class UWeaponPickUpInterface : public UInterface
{
	GENERATED_BODY()
};

class DCIH_MULTITPSGAME_API IWeaponPickUpInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PickUpWeapon(class UWeaponDataAsset* WeaponDataAsset);
	
};