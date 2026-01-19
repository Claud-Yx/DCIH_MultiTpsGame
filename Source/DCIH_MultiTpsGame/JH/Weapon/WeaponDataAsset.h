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
	// ====== UI / 기본 정보 ======
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Info")
	FName WeaponID = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Info")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Info")
	EWeaponCategory Category = EWeaponCategory::Ranged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Info")
	EWeaponType WeaponType = EWeaponType::Rifle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|UI")
	TObjectPtr<UTexture2D> Icon = nullptr;


	// 인벤토리에서 장착할 때 이 클래스를 Spawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Spawn")
	TSubclassOf<AActor> WeaponClass; // 추천: AWeaponBase*로 바꿔도 됨

	// ====== 월드에 떨어진 모습 ======
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Pickup")
	TObjectPtr<UStaticMesh> PickupMesh = nullptr;

	// ====== 장착 관련 ======
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Equip")
	FName AttachSocketName = TEXT("WeaponSocket");

	// ====== 탄약(원거리용) ======
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Ammo", meta = (EditCondition = "Category==EWeaponCategory::Ranged"))
	int32 MaxAmmoInMag = 30;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Ammo", meta = (EditCondition = "Category==EWeaponCategory::Ranged"))
	int32 MaxAmmoTotal = 120;
	
};
