// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MT_Character.h"
#include "YG_PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DCIH_MULTITPSGAME_API AYG_PlayerCharacter : public AMT_Character
{
	GENERATED_BODY()

public:
	AYG_PlayerCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<class UCameraComponent> MainCamera;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<class USpringArmComponent> MainCameraBoom;
};
