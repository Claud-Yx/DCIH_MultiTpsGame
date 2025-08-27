// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JHCharacter.generated.h"

UCLASS()
class DCIH_MULTITPSGAME_API AJHCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AJHCharacter();

	void Move(const FVector2D Axis);
	void Look(const FVector2D Axis);
	void StartJump();
	void StopJump();
	void StartSprint();
	void StopSprint();
	void Fire();


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere)
	class ARifle* EquippedRifle;   // 현재 들고 있는 라이플

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "150.0", ClampMax = "1200.0"))
	float WalkSpeed = 450.f;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "150.0", ClampMax = "1600.0"))
	float SprintSpeed = 700.f;




	void ApplySpeed(float NewSpeed);
};
