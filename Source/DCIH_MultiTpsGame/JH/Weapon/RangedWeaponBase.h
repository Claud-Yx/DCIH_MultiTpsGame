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
// public:
// 	 virtual void Tick(float DeltaTime) override;


public:
	virtual void Attack() override { Fire(); }

	UFUNCTION(BlueprintCallable, Category = "Fire")
	virtual void Fire();

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

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void ApplyRecoil();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void RecoilRecovery(float DeltaTime);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Socket")
	FName MuzzleSocketName;

	UPROPERTY(EditAnywhere, Category = "Trace")
	TEnumAsByte<ECollisionChannel> TraceChannel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TraceRange")
	float TraceRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rate")
	float FireRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rate")
	float LastFireTime;
	FTimerHandle FireTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	int32 CurAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Fire", meta = (ClampMin = "0.1", ClampMax = "10.0"))
	float ReloadTime;
	FTimerHandle ReloadTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	TSubclassOf<UCameraShakeBase> RecoilShake;

	UPROPERTY(EditDefaultsOnly, Category = "Recoil")
	float RecoilVerticalMin = -0.2f;
	UPROPERTY(EditDefaultsOnly, Category = "Recoil")
	float RecoilVerticalMax = 0.2f;
	UPROPERTY(EditDefaultsOnly, Category = "Recoil")
	float RecoilHorizontalMin = -0.2f;
	UPROPERTY(EditDefaultsOnly, Category = "Recoil")
	float RecoilHorizontalMax = 0.2f;

	// 반동 복귀 속도
	UPROPERTY(EditDefaultsOnly, Category = "Recoil")
	float RecoilRecoverySpeed = 5.0f;

	// 현재 누적된 반동량
	FVector2D RecoilValue;

	FRotator PastRotation;
};
