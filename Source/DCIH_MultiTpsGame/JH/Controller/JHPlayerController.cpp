#include "JH/Controller/JHPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "JH/Character/JHCharacter.h"
#include "InputActionValue.h" 
#include "Blueprint/UserWidget.h"
#include "JH/UI/UIManager.h"
#include "JH/Components/HealthComponent.h"



AJHPlayerController::AJHPlayerController()
{
	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableMouseOverEvents = false;

	// UIManager = CreateDefaultSubObject <UIManager>(TEXT("UIManager"));
}

void AJHPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AddDefaultMappingContext();

	// InitializeUIManager();

}

void AJHPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	// AddDefaultMappingContext();
	CacheCharacter();

	InitializeUIManager();

	BindHealthComponentToUI();

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

void AJHPlayerController::CacheCharacter()
{
	if (CachedCharacter.IsValid()) return;

	CachedCharacter = Cast<AJHCharacter>(GetPawn());
}

void AJHPlayerController::InitializeUIManager()
{
	if (UIManager) return;

	if (!UIManagerClass) return;

	UIManager = NewObject<UUIManager>(this, UIManagerClass);
	UIManager->RegisterComponent(); //  실제 월드에 등록됨
	if (UIManager)
	{
		UIManager->Init(this);

		// BindHealthComponentToUI();
	}

}

void AJHPlayerController::BindHealthComponentToUI()
{
	if (!UIManager || !CachedCharacter.IsValid()) return;

	// if(CacheCharacter->healthComp)
	if (UHealthComponent* HealthComp = CachedCharacter->FindComponentByClass<UHealthComponent>())
	{
		// HealthComponent의 OnHealthChanged 이벤트에 UIManager의 OnHealthChanged 함수를 바인딩
		HealthComp->OnHealthChanged.AddUniqueDynamic(UIManager, &UUIManager::OnHealthChanged);

		UIManager->OnHealthChanged(HealthComp->GetCurrentHealth(), HealthComp->GetMaxHealth());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" Failed to find HealthComponent on character."));
	}
}



// ====== Input Callbacks =====
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