// Fill out your copyright notice in the Description page of Project Settings.


#include "YG/Player/YG_PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
	
}
