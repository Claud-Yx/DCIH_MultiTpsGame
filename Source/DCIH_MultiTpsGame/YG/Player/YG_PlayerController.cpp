// Fill out your copyright notice in the Description page of Project Settings.


#include "YG/Player/YG_PlayerController.h"

#include "YG_CheatManager.h"
#include "YG/Component/YGC_InputSystemManager.h"

AYG_PlayerController::AYG_PlayerController()
	: Super()
{
	InputSystemManager = CreateDefaultSubobject<UYGC_InputSystemManager>( TEXT( "InputSystemManager" ) );
	CheatClass         = UYG_CheatManager::StaticClass();
}

void AYG_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputSystemManager->SetPlayer( this );
}

void AYG_PlayerController::ClearImc_Implementation()
{
	InputSystemManager->ClearImc();
}

void AYG_PlayerController::AddImc_Implementation( EYG_InputMappingContext      ImcIndex, int32 Priority,
                                                  const FModifyContextOptions& Options )
{
	InputSystemManager->AddImc( ImcIndex, Priority, Options );
}

bool AYG_PlayerController::RemoveImc_Implementation( EYG_InputMappingContext      ImcIndex,
                                                     const FModifyContextOptions& Options )
{
	return InputSystemManager->RemoveImc( ImcIndex, Options );
}

bool AYG_PlayerController::HasImc_Implementation( EYG_InputMappingContext ImcIndex )
{
	return InputSystemManager->HasImc( ImcIndex );
}

void AYG_PlayerController::ChangeInputModeUiOnly_Implementation( UUserWidget*   TargetWidget,
                                                                 EMouseLockMode InMouseLockMode,
                                                                 bool           bHideCursorDuringCapture )
{
	InputSystemManager->ChangeInputModeUiOnly( TargetWidget, InMouseLockMode, bHideCursorDuringCapture );
}

UInputMappingContext* AYG_PlayerController::GetImc_Implementation( EYG_InputMappingContext Name )
{
	return InputSystemManager->GetImc( Name );
}

UInputAction* AYG_PlayerController::GetIa_Implementation( EYG_InputAction Name )
{
	return InputSystemManager->GetIa( Name );
}
