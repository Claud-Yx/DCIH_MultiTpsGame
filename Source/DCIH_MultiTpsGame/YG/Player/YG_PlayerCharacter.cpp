// Fill out your copyright notice in the Description page of Project Settings.


#include "YG/Player/YG_PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "YG/Interface/YGI_InputSystem.h"

AYG_PlayerCharacter::AYG_PlayerCharacter()
	:Super()
{
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("MainCameraBoom"));

	MainCameraBoom->SetupAttachment(RootComponent);
	MainCamera->SetupAttachment(MainCameraBoom);
}

void AYG_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto InController = GetController();
	auto EnhancedInputComponent = CastChecked<UEnhancedInputComponent>( PlayerInputComponent );

	IF_IMPLEMENTS_InputSystem(InController)
	{
		INTERFACE_InputSystem_AddImc(InController, EYG_InputMappingContext::PlayerCharacter_DefaultMovement, 0, {} );

		EnhancedInputComponent->BindAction(INTERFACE_InputSystem_GetIa(InController, EYG_InputAction::TpsMove), ETriggerEvent::Triggered, this, &ThisClass::MoveOnTps);
		EnhancedInputComponent->BindAction(INTERFACE_InputSystem_GetIa(InController, EYG_InputAction::TpsLook), ETriggerEvent::Triggered, this, &ThisClass::LookOnTps);
		
	}

}

void AYG_PlayerCharacter::MoveOnTps(const FInputActionValue& Value)
{
	FVector MovementVector = Value.Get<FVector>();

	const FRotator DirectionVector = FRotator( 0.f, Controller->GetControlRotation().Yaw, 0.f );

	const FVector ForwardDirection = FRotationMatrix( DirectionVector ).GetUnitAxis( EAxis::X );
	const FVector RightDirection   = FRotationMatrix( DirectionVector ).GetUnitAxis( EAxis::Y );

	AddMovementInput( ForwardDirection, MovementVector.X );
	AddMovementInput( RightDirection, MovementVector.Y );
}

void AYG_PlayerCharacter::LookOnTps(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput( LookAxisVector.X );
	AddControllerPitchInput( LookAxisVector.Y );
}
