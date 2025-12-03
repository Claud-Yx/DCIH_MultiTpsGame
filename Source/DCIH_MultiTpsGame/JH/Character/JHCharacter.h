#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JH/Enum/E_CharacterState.h"
#include "JH/Enum/E_TurnInPlace.h"
#include "JH/UI/Interface/HealthProviderInterface.h"
#include "JH/Delegates/HealthDelegate.h"//       ?

#include "JHCharacter.generated.h"

UCLASS()
class DCIH_MULTITPSGAME_API AJHCharacter 
	: 
	public ACharacter, 
	public IHealthProviderInterface

{
	GENERATED_BODY()

public:
	AJHCharacter();

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
	UFUNCTION(BlueprintCallable, Category = "Input")
	void Attack();

	UFUNCTION(BlueprintCallable, Category = "State")
	FORCEINLINE ECharacterState GetState() const { return CurrentState; }

	UFUNCTION(BlueprintPure, Category = "Aim Offset")
	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }
	
	UFUNCTION(BlueprintPure, Category = "Aim Offset")
	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }

	UFUNCTION(BlueprintPure, Category = "Weapon")
	FORCEINLINE AWeaponBase* GetEquippedWeapon() { return EquippedWeapon; }

	UFUNCTION(BlueprintPure, Category = "Turn In Place")
	FORCEINLINE ETurnInPlace GetTurningInPlace() const { return TurningInPlace; }

	UFUNCTION()
	virtual float GetCurrentHealth_Implementation() override;
	UFUNCTION()
	virtual float GetMaxHealth_Implementation() override;
	UFUNCTION()
	virtual FOnHealthChanged& GetHealthChangedDelegate() override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	void InitializeCharacter();
	void InitializeCamera();
	void InitializeWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UHealthComponent> HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	ECharacterState CurrentState;

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
	void TakeDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void ApplyHeal(float HealAmount);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "150.0", ClampMax = "1200.0"))
	float WalkSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "150.0", ClampMax = "1600.0"))
	float SprintSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AWeaponBase> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AWeaponBase> EquippedWeapon;

	FRotator StartingAimRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aim Offset", meta = (AllowPrivateAccess = "true"))
	float AO_Yaw;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aim Offset", meta = (AllowPrivateAccess = "true"))
	float AO_Pitch;

	float InterpAO_Yaw;

	void CalculateAimOffset(float DeltaTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = "true"))
	ETurnInPlace TurningInPlace;

	void TurnInPlace(float DeltaTime);




public:
	//virtual FOnProviderHealthChanged& GetOnHealthChangedDelegate() override;


	//UFUNCTION()
	//void HandleHealthChanged(float Cur, float Max);
private:
	// UPROPERTY()
	// FOnProviderHealthChanged ProviderHealthEvent;
};
