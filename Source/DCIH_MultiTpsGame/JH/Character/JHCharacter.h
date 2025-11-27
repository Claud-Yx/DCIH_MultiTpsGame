#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JH/Enum/E_CharacterState.h"
#include "JH/Enum/E_TurnInPlace.h"
#include "JH/UI/Interface/StatUpdatable.h"
#include "JHCharacter.generated.h"

UCLASS()
class DCIH_MULTITPSGAME_API AJHCharacter : 
	public ACharacter, public IStatUpdatable
{
	GENERATED_BODY()

public:
	AJHCharacter();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	// ========== Component ==========
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> CameraComp;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UHealthComponent> HealthComp;
public:
	virtual UHealthComponent* GetHealthComponent() override { return HealthComp; }
	virtual void HealthUpdate(float Current, float Max) override {}

	//========= Input ==========
public:
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


	// ========= State ==========
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	ECharacterState CurrentState;
public:
	UFUNCTION(BlueprintCallable, Category = "State")
	void SetState(ECharacterState NewState);

	UFUNCTION(BlueprintCallable, Category = "State")
	FORCEINLINE ECharacterState GetState() const { return CurrentState; }
	
	UFUNCTION(BlueprintPure, Category = "State")
	bool CanFire() const;


	//  ========= Movement ==========
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "150.0", ClampMax = "1200.0"))
	float WalkSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "150.0", ClampMax = "1600.0"))
	float SprintSpeed;

	void ApplySpeed(float NewSpeed);



	// ========= Health ==========

public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	void ApplyDamages(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(float HealAmount);


	// ========== Weapon ==========
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AWeaponBase> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AWeaponBase> EquippedWeapon;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipWeapon(AWeaponBase* Weapon);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void UnEquipWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void DropWeapon();

	UFUNCTION(BlueprintPure, Category = "Weapon")
	FORCEINLINE AWeaponBase* GetEquippedWeapon() { return EquippedWeapon; }



	// ========== Aim Offset ==========
private:
	FRotator StartingAimRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aim Offset", meta = (AllowPrivateAccess = "true"))
	float AO_Yaw;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aim Offset", meta = (AllowPrivateAccess = "true"))
	float AO_Pitch;

	float InterpAO_Yaw;

	void CalculateAimOffset(float DeltaTime);

public:
	UFUNCTION(BlueprintPure, Category = "Aim Offset")
	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }
	UFUNCTION(BlueprintPure, Category = "Aim Offset")
	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }



	//========== Turn In Place ==========
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = "true"))
	ETurnInPlace TurningInPlace;

	void TurnInPlace(float DeltaTime);

public:
	UFUNCTION(BlueprintPure, Category = "Turn In Place")
	FORCEINLINE ETurnInPlace GetTurningInPlace() const { return TurningInPlace; }



		// ========== Initialize ==========
private:
	void InitializeCharacter();
	void InitializeCamera();
	void InitializeWeapon();
	// void InitializeHealth();
};
