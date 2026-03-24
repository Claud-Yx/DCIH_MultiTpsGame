#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JH/Enum/E_WeaponTypes.h"
#include "WeaponDataAsset.generated.h"


USTRUCT(BlueprintType)
struct FRecoilConfig2
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Recoil")
	float VerticalMin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recoil")
	float VerticalMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recoil")
	float HorizontalMin;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recoil")
	float HorizontalMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recoil")
	float RecoverySpeed;
};

UCLASS(BlueprintType)
class DCIH_MULTITPSGAME_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	// ====== Info ======
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Info")
	EWeaponCategory Category;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Info")
	EWeaponType Type;

	
	// ===== Socket ======
	UPROPERTY(EditDefaultsOnly)
	FName HandSocket;

	UPROPERTY(EditDefaultsOnly)
	FName HolsterSocket;


	// ====== Combat ====== 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Combat")
	float Damage;										  
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Combat")
	float FireRate;										  
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Combat")
	float ReloadTime;									  
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Combat")
	float TraceRange;									  
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Combat")
	int32 MaxAmmo;										  
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Combat")
	int32 MagazineAmmo;


	// ====== Recoil ======
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Recoil")
	FRecoilConfig2 RecoilConfig;
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Spawn")
	TSubclassOf<AActor> WeaponClass;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Pickup")
	// TObjectPtr<UStaticMesh> PickupMesh = nullptr;
};
