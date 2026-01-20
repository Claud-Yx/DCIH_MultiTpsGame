// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponDataAsset.generated.h"

UENUM(BlueprintType)
enum class EWeaponCategory : uint8
{
	Ranged UMETA(DisplayName = "Ranged"),
	Melee  UMETA(DisplayName = "Melee")
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Rifle         UMETA(DisplayName = "Rifle"),
	Shotgun       UMETA(DisplayName = "Shotgun"),
	Sniper        UMETA(DisplayName = "Sniper"),
	RocketLauncher UMETA(DisplayName = "RocketLauncher"),

	Bayonet       UMETA(DisplayName = "Bayonet"),
	DoubleSword   UMETA(DisplayName = "DoubleSword"),
	Dagger        UMETA(DisplayName = "Dagger")
};

UCLASS(BlueprintType)
class DCIH_MULTITPSGAME_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Info")
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Spawn")
	TSubclassOf<AActor> WeaponClass;

	// ====== 월드에 떨어진 모습 ======
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Pickup")
	TObjectPtr<UStaticMesh> PickupMesh = nullptr;
	
};
