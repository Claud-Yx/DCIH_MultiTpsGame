#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "AmmoUIInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChanged, int32, Current, int32, Max);
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAmmoUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DCIH_MULTITPSGAME_API IAmmoUIInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	int32 GetCurrentAmmo() const;
	UFUNCTION(BlueprintNativeEvent)
	int32 GetMaxAmmo() const;


	virtual FOnAmmoChanged& GetAmmoChangedDelegate() = 0;
};
