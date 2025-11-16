#pragma once

#include "CoreMinimal.h"
#include "JH/Weapon/WeaponBase.h"
#include "RangedWeaponBase.generated.h"



USTRUCT(BlueprintType)
struct FRecoilConfig
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Recoil")
	float RecoilVerticalMin;
	UPROPERTY(EditDefaultsOnly, Category = "Recoil")
	float RecoilVerticalMax;
	UPROPERTY(EditDefaultsOnly, Category = "Recoil")
	float RecoilHorizontalMin;
	UPROPERTY(EditDefaultsOnly, Category = "Recoil")
	float RecoilHorizontalMax;

	// 반동 복귀 속도
	UPROPERTY(EditDefaultsOnly, Category = "Recoil")
	float RecoilRecoverySpeed;

	float CurrentRecoilVertical = 0.f;
	// float CurrentRecoilHorizontal = 0.f;

	//// 현재 누적된 반동량
	//FVector2D RecoilValue;

	//FRotator PastRotation;

};

UCLASS(Abstract)
class DCIH_MULTITPSGAME_API ARangedWeaponBase : public AWeaponBase
{
	GENERATED_BODY()

public:
	ARangedWeaponBase();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;


protected:
	virtual void Attack() override { Fire(); }

	UFUNCTION(BlueprintCallable, Category = "Fire")
	virtual void Fire();

protected:
	UFUNCTION(BlueprintPure, Category = "Fire")
	FVector GetMuzzleLocation() const;

	UFUNCTION(BlueprintPure, Category = "Fire")
	FVector GetAimPoint() const;

	UFUNCTION(BlueprintPure, Category = "Fire")
	bool CanFire();

	UFUNCTION(BlueprintCallable, Category = "Reload")
	void Reload();

	UFUNCTION(BlueprintCallable, Category = "Reload")
	void FinishReload();

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void ApplyRecoil();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void RecoilRecovery(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ApplyDamage(const FHitResult& Hit, const FVector& ShotDir);


	//UFUNCTION(BlueprintCallable, Category = "Fire")
	//void 

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recoil")
	FRecoilConfig RecoilConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fire")
	bool bCanFire;



	
	// float GetMouseControllPitch(float DeltaTime) const { return MouseControllPitch; }


	UPROPERTY(BlueprintReadOnly)
	bool bLastFireSuccess = false;	// 부모 통과하고 자식이 쏘는 오류

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void DrawDebugTrace(const FVector& ShotDir, const FHitResult& Hit, const bool bHit) const;
	
	float MouseControllPitch = 0.f;

	bool bOwnerValid = false;

};
