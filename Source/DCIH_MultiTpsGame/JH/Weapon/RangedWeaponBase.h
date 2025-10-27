#pragma once

#include "CoreMinimal.h"
#include "JH/Weapon/WeaponBase.h"
#include "RangedWeaponBase.generated.h"

UCLASS(Abstract)
class DCIH_MULTITPSGAME_API ARangedWeaponBase : public AWeaponBase
{
	GENERATED_BODY()

public:
	ARangedWeaponBase();
protected:
	virtual void BeginPlay() override;



protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Socket")
	FName MuzzleSocketName;

	UPROPERTY(EditAnywhere, Category = "Trace")
	TEnumAsByte<ECollisionChannel> TraceChannel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TraceRange")
	float TraceRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rate")
	float FireRate;
	float LastFireTime;
	FTimerHandle FireTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Fire", meta = (ClampMin = "0.1", ClampMax = "10.0"))
	float ReloadTime;
	FTimerHandle ReloadTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	int32 CurAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float Damage;



protected:
	
	UFUNCTION(BlueprintPure, Category = "Fire")
	FVector GetMuzzleLocation() const;

	UFUNCTION(BlueprintPure, Category = "Fire")
	FVector GetAimPoint() const;

	UFUNCTION(BlueprintPure, Category = "Fire")
	bool CanFire() const;



	UFUNCTION(BlueprintCallable, Category = "Reload")
	void Reload();

	UFUNCTION(BlueprintCallable, Category = "Reload")
	void FinishReload();



public:
	virtual void Attack() override { Fire(); }

	UFUNCTION(BlueprintCallable, Category = "Fire")
	virtual void Fire();
};
