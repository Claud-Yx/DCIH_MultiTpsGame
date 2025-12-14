#include "JH/Controller/JHPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "JH/Character/JHCharacter.h"
#include "InputActionValue.h" 
#include "Blueprint/UserWidget.h"
#include "JH/UI/UIManager.h"
#include "JH/Components/HealthComponent.h"
#include "JH/Weapon/WeaponBase.h"


AJHPlayerController::AJHPlayerController()
{
	UIManager = CreateDefaultSubobject<UUIManager>(TEXT("UIManager"));
	// Go to BP and set UIManagerClass to BP_UIManager
}

// Called Before BeginPlay
void AJHPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!CachedCharacter.IsValid()) {
		CachedCharacter = Cast<AJHCharacter>(InPawn);
	}
	if (CachedCharacter.IsValid())
	{
		CachedCharacter->OnWeaponEquipped.AddUObject(
			this, &AJHPlayerController::HandleWeaponEquipped
		);
	}
	// InitializeUIManager();
	// BindHealthComponentToUI();
}
void AJHPlayerController::HandleWeaponEquipped(AWeaponBase* Weapon)
{
	UIManager->RegisterUIObject(Weapon);
}

void AJHPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AddDefaultMappingContext();
	InitializeUIManager();
	// InitializeUIManager();

	// InitializeUIManager();

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
			EIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AJHPlayerController::OnJumpStarted);
			EIC->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AJHPlayerController::OnJumpCompleted);
			EIC->BindAction(IA_Jump, ETriggerEvent::Canceled, this, &AJHPlayerController::OnJumpCompleted);
		}

		if (ensureMsgf(IA_Fire, TEXT("IA_Jump not assigned")))
		{
			EIC->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AJHPlayerController::OnAttack);
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

void AJHPlayerController::InitializeUIManager() // Actor 타입의 오브젝트 UI 연결
{
	// if (!UIManager) return;
	// if (!UIManagerClass) return;

	// UIManager = NewObject<UUIManager>(this, UIManagerClass);
	UIManager->Init();



	// 연결 하고 싶은 것 가져와서 UIManager에 등록
	if (CachedCharacter.IsValid())
	{
		// 어떤 캐릭터든 상관없이 UIManager는 인터페이스만 본다
		UIManager->RegisterUIObject(CachedCharacter.Get());

		// 캐릭터가 어떤 무기를 들고 있든 그대로 전달
		if (AActor* Weapon = Cast<AActor>(CachedCharacter->GetEquippedWeapon()))
		{
			UIManager->RegisterUIObject(Weapon);
		}
	}
	// UIManager->ResgisterUIObject(CachedCharacter->);

	// UIManager->Init(this);
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