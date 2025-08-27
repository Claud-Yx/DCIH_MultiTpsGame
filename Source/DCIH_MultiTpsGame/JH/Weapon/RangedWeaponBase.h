#pragma once

#include "CoreMinimal.h"
#include "JH/Weapon/WeaponBase.h"
#include "RangedWeaponBase.generated.h"

class APawn;

UCLASS(Abstract)
class DCIH_MULTITPSGAME_API ARangedWeaponBase : public AWeaponBase
{
	GENERATED_BODY()

public:
	ARangedWeaponBase();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Fire")
	virtual void Fire();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Reload")
	void Reload();

	bool CanFire() const;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void FinishReload();

	FVector GetMuzzleLocation() const;

	FVector GetAimPoint() const;

	FVector GetShotDirection(FVector& OutMuzzleLoc, FVector& OutTraceEnd) const;


protected:
	// ===========================
	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Sockets")
	FName MuzzleSocketName = "Muzzle";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Trace")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	// ===========================
	// Ω∫≈»
	// ===========================
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Stats")
	float TraceRange = 20000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Stats")
	float Damage = 30.f;

	// ===========================
	// ≈∫æ‡
	// ===========================
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Ammo")
	int32 Ammo = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Ammo")
	int32 MaxAmmo = 30;
	UPROPERTY(EditAnywhere, Category = "Weapon|Tuning")
	float ReloadTime = 2.f;

protected:
	FTimerHandle ReloadTimerHandle;
};
