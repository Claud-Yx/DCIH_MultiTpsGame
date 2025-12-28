#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "AmmoUIInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnAmmoChanged, 
	int32, Current, 
	int32, Max);



UINTERFACE(MinimalAPI)
class UAmmoUIInterface : public UInterface
{
	GENERATED_BODY()
};


class DCIH_MULTITPSGAME_API IAmmoUIInterface
{
	GENERATED_BODY()

public:

	virtual FOnAmmoChanged& GetAmmoChangedDelegate() = 0;

	//UFUNCTION(BlueprintNativeEvent)
	//void AddMagazine(int32 Count);

	UFUNCTION(BlueprintNativeEvent)
	int32 GetCurrentAmmo() const;

	UFUNCTION(BlueprintNativeEvent)
	int32 GetMaxAmmo() const;

	//UFUNCTION(BlueprintNativeEvent)
	//int32 GetMagazineNum() const;
	
};
