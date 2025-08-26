// Fill out your copyright notice in the Description page of Project Settings.


#include "YG/Component/YGC_InputSystemManager.h"

#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "YG/DataAsset/YGDAB_InputDefinition.h"
#include "YG/Player/YG_PlayerController.h"

#define GetPlayerController() Cast<AYG_PlayerController>(OwnerPlayer)
#define IF_EILPS(PlayerController) if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))

// Sets default values for this component's properties
UYGC_InputSystemManager::UYGC_InputSystemManager()
{
}

void UYGC_InputSystemManager::ClearImc()
{
	IF_EILPS(GetPlayerController())
	{
		Subsystem->ClearAllMappings();
	}
}

void UYGC_InputSystemManager::AddImc(EYG_InputMappingContext ImcIndex, int32 Priority,
                                     const FModifyContextOptions& Options)
{
	IF_EILPS(GetPlayerController())
	{
		if (auto Imc = GetImc(ImcIndex))
		{
			Subsystem->AddMappingContext(Imc, Priority, Options);
		}
	}
}

bool UYGC_InputSystemManager::RemoveImc(EYG_InputMappingContext ImcIndex, const FModifyContextOptions& Options)
{
	IF_EILPS(GetPlayerController())
	{
		if (HasImc(ImcIndex))
		{
			Subsystem->RemoveMappingContext(GetImc(ImcIndex), Options);
			return true;
		}
	}

	return false;
}

bool UYGC_InputSystemManager::HasImc(EYG_InputMappingContext ImcIndex)
{
	IF_EILPS(GetPlayerController())
	{
		if (auto Imc = GetImc(ImcIndex))
		{
			return Subsystem->HasMappingContext(Imc);
		}
	}

	return false;
}

void UYGC_InputSystemManager::ChangeInputModeGameOnly(bool bConsumeCaptureMouseDown, bool bShowMouseCursor)
{
	auto PlayerController = GetPlayerController();

	PlayerController->bShowMouseCursor = false;
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown( bConsumeCaptureMouseDown );
	PlayerController->SetShowMouseCursor( bShowMouseCursor );
	PlayerController->SetInputMode( InputMode );
}

void UYGC_InputSystemManager::ChangeInputModeUiOnly(UUserWidget* TargetWidget, EMouseLockMode InMouseLockMode,
                                                    bool bHideCursorDuringCapture)
{
	auto PlayerController = GetPlayerController();

	PlayerController->bShowMouseCursor = true;

	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus( TargetWidget->TakeWidget() );
	InputMode.SetLockMouseToViewportBehavior( InMouseLockMode );
	InputMode.SetHideCursorDuringCapture( bHideCursorDuringCapture );
	PlayerController->SetInputMode( InputMode );
}

UInputMappingContext* UYGC_InputSystemManager::GetImc(EYG_InputMappingContext Name)
{
	check( InputDefinition );
	return InputDefinition->GetImc( Name );
}

UInputAction* UYGC_InputSystemManager::GetIa(EYG_InputAction Name)
{
	check( InputDefinition );
	return InputDefinition->GetIa( Name );
}
