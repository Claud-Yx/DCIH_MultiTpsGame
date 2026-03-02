#include "JH/Controller/JHPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "JH/Character/JHCharacter.h"
#include "InputActionValue.h" 
#include "Blueprint/UserWidget.h"
#include "JH/UI/UIManager.h"
#include "JH/Components/HealthComponent.h"
#include "JH/Components/StaminaComponent.h"
#include "JH/Weapon/WeaponBase.h"


AJHPlayerController::AJHPlayerController()    
{
	// *** Go to BP and set UIManagerClass to BP_UIManager
	UIManager = CreateDefaultSubobject<UUIManager>(TEXT("UIManager"));
}

// Called Before BeginPlay
void AJHPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!CachedCharacter.IsValid()) {
		CachedCharacter = Cast<AJHCharacter>(InPawn);
	}

	// UI Create
	UIManager->Init();

	// Binding Components in Character to UI
	if (CachedCharacter.IsValid())
	{
		UIManager->RegisterUIObject(CachedCharacter.Get());	// Health
		UIManager->RegisterUIObject(CachedCharacter->GetStaminaComponent()); // Stamina
		UIManager->RegisterUIObject(CachedCharacter->GetEquippedWeapon()); // Ammo
	}

	// Called when Character Equip Weapon
	if (CachedCharacter.IsValid())
	{
		CachedCharacter->OnWeaponEquipped.
			AddUObject(this, &AJHPlayerController::HandleWeaponEquipped);
		// Delegate's Type is WeaponBase
	}
}

// Reciever's Type is WeaponBase
void AJHPlayerController::HandleWeaponEquipped(AWeaponBase* Weapon)
{
	UIManager->RegisterUIObject(Weapon);
}

void AJHPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AddDefaultMappingContext();

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
			EIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &AJHPlayerController::OnJumpStarted);
			EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AJHPlayerController::OnJumpCompleted);
			EIC->BindAction(IA_Jump, ETriggerEvent::Canceled, this, &AJHPlayerController::OnJumpCompleted);
		}

		if (ensureMsgf(IA_Fire, TEXT("IA_Jump not assigned")))
		{
			EIC->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AJHPlayerController::OnAttack);
		}
		
		if (ensureMsgf(IA_Aim, TEXT("IA_AIM not assigned")))
		{
			EIC->BindAction(IA_Aim, ETriggerEvent::Started, this, &AJHPlayerController::OnAimStart);
			EIC->BindAction(IA_Aim, ETriggerEvent::Completed, this, &AJHPlayerController::OnAimEnd);
		}

		if (ensureMsgf(IA_Aim, TEXT("IA_AIM not assigned")))
		{
			EIC->BindAction(IA_Reload, ETriggerEvent::Started, this, &AJHPlayerController::OnReload);
		}

		if (ensureMsgf(IA_Crouch, TEXT("IA_Crouch not assigned")))
		{
			EIC->BindAction(IA_Crouch, ETriggerEvent::Started, this, &AJHPlayerController::OnCrouchToggle);
			// EIC->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &AJHPlayerController::OnUnCrouch);
		}

		if (ensureMsgf(IA_Roll, TEXT("IA_Roll not assigned")))
		{
			EIC->BindAction(IA_Roll, ETriggerEvent::Completed, this, &AJHPlayerController::OnRoll);
		}

		if (ensureMsgf(IA_Prone, TEXT("IA_Prone not assigned")))
		{
			EIC->BindAction(IA_Prone, ETriggerEvent::Completed, this, &AJHPlayerController::OnProneToggle);
		}

		if (ensureMsgf(IA_WeaponChange_1, TEXT("IA_Prone not assigned")))
		{
			EIC->BindAction(IA_WeaponChange_1, ETriggerEvent::Completed, this, &AJHPlayerController::OnWeaponChange1);
		}
		if (ensureMsgf(IA_WeaponChange_2, TEXT("IA_Prone not assigned")))
		{
			EIC->BindAction(IA_WeaponChange_2, ETriggerEvent::Completed, this, &AJHPlayerController::OnWeaponChange2);
		}
		if (ensureMsgf(IA_PickUp, TEXT("IA_PickUp not assigned")))
		{
			EIC->BindAction(IA_PickUp, ETriggerEvent::Started, this, &AJHPlayerController::OnPickUp);
		}

	}
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

void AJHPlayerController::OnMove(const FInputActionValue& Value)
{
	if (CachedCharacter.IsValid())
		CachedCharacter->Move(Value.Get<FVector2D>());
}

void AJHPlayerController::OnLook(const FInputActionValue& Value)
{
	FVector2D Look = Value.Get<FVector2D>();

	MousePitch += Look.Y;

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

void AJHPlayerController::OnAttack()
{
	if (CachedCharacter.IsValid())
		CachedCharacter->Attack();
}

void AJHPlayerController::OnAimStart()
{
	if(CachedCharacter.IsValid())
		CachedCharacter->AimStart();
}

void AJHPlayerController::OnAimEnd()
{
	if (CachedCharacter.IsValid())
		CachedCharacter->AimEnd();
}

void AJHPlayerController::OnReload()
{
	if (CachedCharacter.IsValid())
		CachedCharacter->Reload();
}

void AJHPlayerController::OnCrouchToggle()
{
	if (CachedCharacter->IsCrouched()) 
	{
		CachedCharacter->UnCrouch();
	}
	else {
		CachedCharacter->Crouch();
	}
}



void AJHPlayerController::OnRoll()
{
	if (CachedCharacter.IsValid())
		CachedCharacter->Roll();
}

void AJHPlayerController::OnProneToggle()
{
	if (CachedCharacter.IsValid())
	{
		if (CachedCharacter->GetIsProne())
		{
			CachedCharacter->UnProne();
		}
		else
		{
			CachedCharacter->Prone();
		}
	}
}

void AJHPlayerController::OnWeaponChange1()
{
	CachedCharacter->SwapWeapon(1);
}

void AJHPlayerController::OnWeaponChange2()
{
	CachedCharacter->SwapWeapon(2);
}

void AJHPlayerController::OnPickUp()
{
	CachedCharacter->PickUp();

}
