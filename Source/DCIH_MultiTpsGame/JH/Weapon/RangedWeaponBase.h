#pragma once

#include "CoreMinimal.h"
#include "JH/Weapon/WeaponBase.h"
#include "RangedWeaponBase.generated.h"

UCLASS(Abstract)
class DCIH_MULTITPSGAME_API ARangedWeaponBase : public AWeaponBase
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Socket")
	FName muzzleSocketName = "Muzzle";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TraceChannel")
	TEnumAsByte<ECollisionChannel> traceChannel = ECC_Visibility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	int32 curAmmo = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	int32 maxAmmo = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TraceRange")
	float traceRange = 20000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float damage = 30.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rate")
	float fireRate;

	float lastFireTime;

	FTimerHandle fireTimerHandle;
	//UPROPERTY(EditAnywhere, Category = "Weapon|Tuning")
	//float ReloadTime = 2.f;

	// FTimerHandle ReloadTimerHandle;



protected:
	ARangedWeaponBase();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Fire")
	bool CanFire() const;



	UFUNCTION(BlueprintCallable, Category = "Reload")
	void Reload();

	UFUNCTION(BlueprintCallable, Category = "Reload")
	void FinishReload();

	UFUNCTION(BlueprintPure, Category = "Fire")
	FVector GetMuzzleLocation() const;

	UFUNCTION(BlueprintPure, Category = "Fire")
	FVector GetAimPoint() const;

	//UFUNCTION(BlueprintPure, Category = "Fire")
	//FVector GetShotDirection() const;

public:
	UFUNCTION(BlueprintCallable, Category = "Fire")
	virtual void Fire();	// 가상 함수

	virtual void Use() override { Fire(); }
};
