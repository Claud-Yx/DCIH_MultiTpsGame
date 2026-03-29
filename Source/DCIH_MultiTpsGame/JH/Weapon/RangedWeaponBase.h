#pragma once

#include "CoreMinimal.h"
#include "JH/Weapon/WeaponBase.h"
#include "JH/UI/Interface/AmmoUIInterface.h"
#include "RangedWeaponBase.generated.h"

class AJHPlayerController;

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

	// �ݵ� ���� �ӵ�
	UPROPERTY(EditDefaultsOnly, Category = "Recoil")
	float RecoilRecoverySpeed;

	float CurrentRecoilVertical = 0.f;
	// float CurrentRecoilHorizontal = 0.f;

	//// ���� ������ �ݵ���
	//FVector2D RecoilValue;

	//FRotator PastRotation;

};

UCLASS(Abstract)
class DCIH_MULTITPSGAME_API ARangedWeaponBase 
	: 
	public AWeaponBase,
	public IAmmoUIInterface
{
	GENERATED_BODY()

public:
	ARangedWeaponBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Attack() override { Fire(); }

	UFUNCTION(BlueprintCallable, Category = "Reload")
	void Reload();

	virtual int32 GetCurrentAmmo_Implementation() const override { return CurAmmo; }
	virtual int32 GetMaxAmmo_Implementation() const override { return MaxAmmo; }
	virtual FOnAmmoChanged& GetAmmoChangedDelegate() override { return OnAmmoChanged; }

protected:
	virtual void Fire();

private:
	// void Fire();
	void FinishReload();

	bool CanFire() const;
	void ConsumeAmmo(int32 Amount);

	void ApplyRecoil();
	void RecoilRecovery(float DeltaTime);


protected:
	FVector GetMuzzleLocation() const;
	FVector GetAimPoint() const;

	void ApplyHitDamage(const FHitResult& Hit, const FVector& ShotDir);
	void DrawDebugTrace(const FVector& Start, const FVector& End, const FHitResult& Hit, bool bHit) const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ammo")
	int32 CurAmmo = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ammo")
	int32 MaxAmmo = 0;

	// 마지막 Fire()가 실제 발사까지 성공했는지 — FireImpl이 이 값을 보고 작동
	bool bLastFireSuccess = false;

private:
	UPROPERTY()
	FOnAmmoChanged OnAmmoChanged;

	float LastFireTime ;
	float CurrentRecoilVertical;

	FTimerHandle ReloadTimerHandle;

	UPROPERTY()
	TObjectPtr<AJHPlayerController> CachedJHController;

	FName MuzzleSocket = TEXT("Muzzle");

	FRecoilConfig RecoilConfig;

//	UFUNCTION(BlueprintPure, Category = "Fire")
//	bool CanFire();
//
//
//
//	UFUNCTION(BlueprintCallable, Category = "Reload")
//	void FinishReload();
//
//	UFUNCTION(BlueprintCallable, Category = "Fire")
//	void ApplyRecoil();
//
//	UFUNCTION(BlueprintCallable, Category = "Weapon")
//	void RecoilRecovery(float DeltaTime);
//
//	UFUNCTION(BlueprintCallable, Category = "Weapon")
//	void ApplyDamage(const FHitResult& Hit, const FVector& ShotDir);
//
//protected:
//	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Socket")
//	FName MuzzleSocketName;
//
//	UPROPERTY(EditAnywhere, Category = "Trace")
//	TEnumAsByte<ECollisionChannel> TraceChannel;
//
//	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TraceRange")
//	float TraceRange;
//
//	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rate")
//	float FireRate;
//	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rate")
//	float LastFireTime;
//	FTimerHandle FireTimerHandle;
//
//protected:
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
//	int32 CurAmmo;
//
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
//	int32 MaxAmmo;
//
//	FOnAmmoChanged AmmoChangedDelegate;
//
//public:
//	
//	
//	
//	
//	
//	
//	
//	
//	void ConsumeAmmo(int32 Amount);
//protected:
//
//	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
//	float Damage;
//
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Fire", meta = (ClampMin = "0.1", ClampMax = "10.0"))
//	float ReloadTime;
//	FTimerHandle ReloadTimerHandle;
//
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
//	TSubclassOf<UCameraShakeBase> RecoilShake;
//
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Recoil")
//	FRecoilConfig RecoilConfig;
//
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fire")
//	bool bCanFire;
//
//
//
//	
//	// float GetMouseControllPitch(float DeltaTime) const { return MouseControllPitch; }
//
//
//	UPROPERTY(BlueprintReadOnly)
//	bool bLastFireSuccess = false;	// �θ� ����ϰ� �ڽ��� ��� ����
//
//	UFUNCTION(BlueprintCallable, Category = "Fire")
//	void DrawDebugTrace(const FVector& ShotDir, const FHitResult& Hit, const bool bHit) const;
//	
//	float MouseControllPitch = 0.f;
//
//	bool bOwnerValid = false;
//
//	UPROPERTY(BlueprintReadOnly)
//	TObjectPtr <class AJHPlayerController> JHController;
};
