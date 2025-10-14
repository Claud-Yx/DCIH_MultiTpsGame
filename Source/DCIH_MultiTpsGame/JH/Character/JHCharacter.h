#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JH/Enum/E_CharacterState.h"
#include "JH/Enum/E_TurnInPlace.h"
#include "JHCharacter.generated.h"

UCLASS()
class DCIH_MULTITPSGAME_API AJHCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AJHCharacter();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;



	// Initialization
	void InitializeCharacter();
	void InitializeCamera();
	void InitializeHealth();
	void InitializeWeapon();



	// State
	UFUNCTION(BlueprintCallable, Category = "State")
	void SetState(ECharacterState NewState);

	UFUNCTION(BlueprintCallable, Category = "State")
	ECharacterState GetState() const { return CurrentState; }

	bool CanFire() const;



	// Input
	void Move(const FVector2D& Axis);
	void Look(const FVector2D& Axis);
	void StartJump();
	void StopJump();
	void StartSprint();
	void StopSprint();
	void Fire();




protected:


	void AimOffset(float DeltaTime);



public	:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UHealthComponent> healthComp;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class AWeaponBase> EquippedWeapon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = "true"))
	ECharacterState CurrentState = ECharacterState::Idle;

	UPROPERTY(EditDefaultsOnly, Category = "Movement", meta = (ClampMin = "150.0", ClampMax = "1200.0"))
	float WalkSpeed = 400.f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement", meta = (ClampMin = "150.0", ClampMax = "1600.0"))
	float SprintSpeed = 700.f;

	
	void ApplySpeed(float NewSpeed);

	FRotator StartingAimRotation;
	float AO_Yaw;
	float InterpAO_Yaw;
	float AO_Pitch;

	ETurnInPlace TurningInPlace;
	void TurnInPlace(float DeltaTime);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class AWeaponBase> WeaponClass;
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void GetDamage(float damageAmount);

	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }
	FORCEINLINE float GetAO_Pitch() const {return AO_Pitch;}

	FORCEINLINE AWeaponBase*  GetEquippedWeapon() { return EquippedWeapon; }
	

	FORCEINLINE ETurnInPlace GetTurningInPlace() const { return TurningInPlace; }

	// class EquipedWeapon* GetEquippedWeapon() const { return EquippedWeapon; }
};
