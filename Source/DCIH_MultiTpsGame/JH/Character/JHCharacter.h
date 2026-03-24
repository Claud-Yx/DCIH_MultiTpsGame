#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JH/Enum/E_CharacterState.h"
#include "JH/Enum/E_TurnInPlace.h"
#include "JH/UI/Interface/HealthProviderInterface.h"
#include "JH/Delegates/HealthDelegate.h"//       ?
#include "JH/Interface/MagazineInterface.h"
#include "JH/Weapon/WeaponPickUpInterface.h"
#include "JH/Interface/InteractTarget.h"
#include "JH/Enum/E_WeaponTypes.h"

#include "JHCharacter.generated.h"

class AWeaponBase;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponEquipped, AWeaponBase*);
class UWeaponManagerComponent;

UCLASS()
class DCIH_MULTITPSGAME_API AJHCharacter
	:
	public ACharacter,
	public IHealthProviderInterface,
	public IMagazineInterface
{
	GENERATED_BODY()

public:
	AJHCharacter();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


public:	// InterFace
	FOnWeaponEquipped OnWeaponEquipped;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnMagazineChanged OnMagazineChanged;

	FORCEINLINE virtual FOnMagazineChanged& GetMagazineChangedDelegate() override
	{return OnMagazineChanged;}

	virtual void AddMagazine_Implementation() override;

	virtual FOnHealthChanged& GetHealthChangedDelegate() override;
	
	virtual float GetCurrentHealth_Implementation() override;
	virtual float GetMaxHealth_Implementation() override;



public:	// Getter
	UFUNCTION(BlueprintPure, Category = "State")
	FORCEINLINE ECharacterState GetState() const { return CurrentState; }

	UFUNCTION(BlueprintPure, Category = "Aim Offset")
	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }

	UFUNCTION(BlueprintPure, Category = "Aim Offset")
	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }



	UFUNCTION(BlueprintPure, Category = "Weapon")
	FORCEINLINE AWeaponBase* GetEquippedWeapon() { return EquippedWeapon; }



	UFUNCTION(BlueprintPure, Category = "Turn In Place")
	FORCEINLINE ETurnInPlace GetTurningInPlace() const { return TurningInPlace; }

	UFUNCTION(BlueprintPure, Category = "Stamina")
	FORCEINLINE UStaminaComponent* GetStaminaComponent() const { return StaminaComp; };

	UFUNCTION(BlueprintPure, Category = "Crouch")
	FORCEINLINE bool GetIsCrouch() { return IsCrouched(); };

	UFUNCTION(BlueprintPure, Category = "Prone")
	FORCEINLINE bool GetIsProne() { return bIsProne; };

	EWeaponCategory GetCurrentWeaponCategory() const;



	AWeaponBase* GetCurrentWeapon();


	



	// ======================================
	// Input Actions
	// =======================================

public:	// Input Action
	UFUNCTION(BlueprintCallable, Category = "Input")
	void Move(const FVector2D& Axis);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void Look(const FVector2D& Axis);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void StartJump();
	UFUNCTION(BlueprintCallable, Category = "Input")
	void StopJump();
	UFUNCTION(BlueprintCallable, Category = "Input")
	void StartSprint();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void StopSprint();

	virtual void Crouch(bool bClientSimulation = false) override;
	virtual void UnCrouch(bool bClientSimulation = false) override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Attack();

	UFUNCTION(BlueprintCallable, Category = "Input | Aim")
	void AimStart();

	UFUNCTION(BlueprintCallable, Category = "Input | Aim")
	void AimEnd();

	UFUNCTION(BlueprintCallable, Category = "Input | Reload")
	void Reload();

	UFUNCTION(BlueprintCallable, Category = "Input | Roll")
	void Roll();

	UFUNCTION(BlueprintCallable, Category = "Input | Roll")
	void RollEnd();

	UFUNCTION(BlueprintCallable, Category = "Input | Prone")
	void Prone();

	UFUNCTION(BlueprintCallable, Category = "Input | Prone")
	void UnProne();

	UFUNCTION(BlueprintCallable, Category = "Input | ChangeWeapon")
	void SwapWeapon(int WeaponNum);

	UFUNCTION(BlueprintCallable, Category = "Input | PickUp")
	void PickUp();

	//UFUNCTION()
	//void PickUpWeapon_Implementation(class UWeaponDataAsset *WeaponDataAsset);


protected:	// Internal Logic
	UFUNCTION(BlueprintCallable, Category = "State")
	void SetState(ECharacterState NewState);

	UFUNCTION(BlueprintPure, Category = "State")
	bool CanFire() const;

	UFUNCTION(BlueprintCallable, Category = "State")
	void ApplySpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipWeapon(AWeaponBase* Weapon);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void UnEquipWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void DropWeapon();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void HandleDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void ApplyHeal(float HealAmount);

	void CalculateAimOffset(float DeltaTime);

	void TurnInPlace(float DeltaTime);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	void UpdateCharacterOriented();

protected:

	UFUNCTION()
	void ChangeState(ECharacterState NewState);

	UFUNCTION()
	void ChangeWeaponState(ECharacterWeaponState NewState);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	ECharacterState CurrentState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	ECharacterWeaponState CurrentWeaponState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aim | FOV")
	float DefaultFOV;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Aim | FOV")
	float AimFOV;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float SprintSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float CrouchSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float ProneSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float IdleEyeHeight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float CrouchEyeHeight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float ProneEyeHeight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Capsule", meta = (AllowPrivateAccess = "true"))
	float IdleHalfCapsuleHeight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Capsule", meta = (AllowPrivateAccess = "true"))
	float CrouchHalfCapsuleHeight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Capsule", meta = (AllowPrivateAccess = "true"))
	float ProneHalfCapsuleHeight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Capsule", meta = (AllowPrivateAccess = "true"))
	float IdleMeshZ;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Capsule", meta = (AllowPrivateAccess = "true"))
	float CrouchMeshZ;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Capsule", meta = (AllowPrivateAccess = "true"))
	float ProneMeshZ;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AWeaponBase> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AWeaponBase> EquippedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AWeaponBase> HolsterWeapon;


	FRotator StartingAimRotation;

	UPROPERTY(BlueprintReadOnly, Category = "Aim Offset", meta = (AllowPrivateAccess = "true"))
	float AO_Yaw;

	UPROPERTY(BlueprintReadOnly, Category = "Aim Offset", meta = (AllowPrivateAccess = "true"))
	float AO_Pitch;

	float InterpAO_Yaw;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = "true"))
	ETurnInPlace TurningInPlace;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Magazine")
	int32 MagazineNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Magazine")
	bool bIsRolling;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Magazine")
	bool bIsProne;

private:
	void InitializeCharacter();
	void InitializeCamera();
	void InitializeWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHealthComponent> HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaminaComponent> StaminaComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWeaponManagerComponent> WeaponManagerComp;

	UPROPERTY()
	class AWeaponBase* OverlappingWeapon;
	
};