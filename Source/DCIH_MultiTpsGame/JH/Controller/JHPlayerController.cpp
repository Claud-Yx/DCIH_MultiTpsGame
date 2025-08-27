// Fill out your copyright notice in the Description page of Project Settings.


#include "JH/Controller/JHPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "JH/Character/JHCharacter.h"
#include "InputActionValue.h" 


AJHPlayerController::AJHPlayerController()
{
    bShowMouseCursor = false;
    bEnableClickEvents = false;
    bEnableMouseOverEvents = false;
}

void AJHPlayerController::BeginPlay()
{
    Super::BeginPlay();
    AddDefaultMappingContext();
    CacheControlledCharacter();
}

void AJHPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    CacheControlledCharacter();
}

void AJHPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
    {
        if (ensureMsgf(IA_Move, TEXT("IA_Move not assigned")))
            EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AJHPlayerController::OnMove);

        if (ensureMsgf(IA_Look, TEXT("IA_Look not assigned")))
            EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AJHPlayerController::OnLook);

        if (ensureMsgf(IA_Jump, TEXT("IA_Jump not assigned")))
        {
            EIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &AJHPlayerController::OnJumpStarted);
            EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AJHPlayerController::OnJumpCompleted);
            EIC->BindAction(IA_Jump, ETriggerEvent::Canceled, this, &AJHPlayerController::OnJumpCompleted);
        }

        if (ensureMsgf(IA_Sprint, TEXT("IA_Sprint not assigned")))
        {
            EIC->BindAction(IA_Sprint, ETriggerEvent::Started, this, &AJHPlayerController::OnSprintStarted);
            EIC->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &AJHPlayerController::OnSprintCompleted);
            EIC->BindAction(IA_Sprint, ETriggerEvent::Canceled, this, &AJHPlayerController::OnSprintCompleted);
        }

        if (ensureMsgf(IA_Jump, TEXT("IA_Jump not assigned")))
        {
            EIC->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AJHPlayerController::OnJumpStarted);
            EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AJHPlayerController::OnJumpCompleted);
            EIC->BindAction(IA_Jump, ETriggerEvent::Canceled, this, &AJHPlayerController::OnJumpCompleted);
        }
    }
}


//===

void AJHPlayerController::OnMove(const FInputActionValue& Value)
{
    if (CachedCharacter.IsValid())
        CachedCharacter->Move(Value.Get<FVector2D>());
}

void AJHPlayerController::OnLook(const FInputActionValue& Value)
{
    if (CachedCharacter.IsValid())
        CachedCharacter->Look(Value.Get<FVector2D>());
}

void AJHPlayerController::OnJumpStarted()
{
    if (CachedCharacter.IsValid())
        CachedCharacter->StartJump();
}

void AJHPlayerController::OnJumpCompleted()
{
    if (CachedCharacter.IsValid())
        CachedCharacter->StopJump();
}

void AJHPlayerController::OnSprintStarted()
{
    if (CachedCharacter.IsValid())
        CachedCharacter->StartSprint();
}

void AJHPlayerController::OnSprintCompleted()
{
    if (CachedCharacter.IsValid())
        CachedCharacter->StopSprint();
}


//===


void AJHPlayerController::CacheControlledCharacter()
{
    CachedCharacter = Cast<AJHCharacter>(GetPawn());
}

void AJHPlayerController::AddDefaultMappingContext()
{
    if (!IMC_Default) return;

    if (ULocalPlayer* LP = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsys =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LP))
        {
            Subsys->AddMappingContext(IMC_Default, /*Priority*/0);
        }
    }
}