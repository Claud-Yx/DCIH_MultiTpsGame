#pragma once

#include "CoreMinimal.h"
#include "JH/Weapon/WeaponBase.h"
#include "JH/UI/Interface/AmmoUIInterface.h"
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

	UFUNCTION(BlueprintCallable, Category = "Reload")
	void Reload();

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
	void FinishReload();

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void ApplyRecoil();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void RecoilRecovery(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ApplyDamage(const FHitResult& Hit, const FVector& ShotDir);

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

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	int32 CurAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo")
	int32 MaxAmmo;

	FOnAmmoChanged AmmoChangedDelegate;

public:
	virtual int32 GetCurrentAmmo_Implementation() const override { return CurAmmo; }
	virtual int32 GetMaxAmmo_Implementation() const override { return MaxAmmo; }
	virtual FOnAmmoChanged& GetAmmoChangedDelegate() override { return AmmoChangedDelegate; }
	
	
	
	
	
	
	
	
	void ConsumeAmmo(int32 Amount);
protected:

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
	bool bLastFireSuccess = false;	// �θ� ����ϰ� �ڽ��� ��� ����

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void DrawDebugTrace(const FVector& ShotDir, const FHitResult& Hit, const bool bHit) const;
	
	float MouseControllPitch = 0.f;

	bool bOwnerValid = false;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr <class AJHPlayerController> JHController;
};
