// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
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

	virtual void SetupPlayerInputComponent( UInputComponent* PlayerInputComponent ) override;

protected:
	virtual void Tick( float DeltaSeconds ) override;

	void MoveOnTps( const FInputActionValue& Value );
	void LookOnTps( const FInputActionValue& Value );

	// Components

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category="Components", meta=(AllowPrivateAccess=true) )
	TObjectPtr<class UCameraComponent> MainCamera;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category="Components", meta=(AllowPrivateAccess=true) )
	TObjectPtr<class USpringArmComponent> MainCameraBoom;

	UPROPERTY( BlueprintReadOnly, VisibleAnywhere, Category="Components", meta=(AllowPrivateAccess=true) )
	TObjectPtr<class UYGC_LineVisualizer> InteractionTracePoint;

	// Props
	UPROPERTY( BlueprintReadOnly, EditAnywhere, Category="YG", meta=(AllowPrivateAccess=true) )
	TEnumAsByte<ECollisionChannel> InteractionTraceChannel;
};
