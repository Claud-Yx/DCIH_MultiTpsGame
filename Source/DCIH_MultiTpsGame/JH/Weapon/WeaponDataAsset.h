#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JH/Enum/E_WeaponTypes.h"
#include "WeaponDataAsset.generated.h"



UCLASS(BlueprintType)
class DCIH_MULTITPSGAME_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Info")
	EWeaponCategory Category;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Info")
	EWeaponType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Spawn")
	TSubclassOf<AActor> WeaponClass;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Pickup")
	// TObjectPtr<UStaticMesh> PickupMesh = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	FName HandSocket;

	UPROPERTY(EditDefaultsOnly)
	FName HolsterSocket;

	
};
