#include "JH/UI/UIManager.h"
#include "GameFramework/PlayerController.h"
#include "JH/UI/MainHUD.h"
#include "JH/UI/Interface/HealthProviderInterface.h"
#include "JH/UI/Interface/AmmoUIInterface.h"
#include "JH/UI/Interface/StaminaUIInterface.h"
#include "JH/Interface/MagazineInterface.h"

UUIManager::UUIManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUIManager::BeginPlay()
{
	Super::BeginPlay();
}

void UUIManager::Init()
{
	OwningController = Cast<APlayerController>(GetOwner());
	if (OwningController.IsValid())
	{
		CreateMainHUD();
	}
}

//void UUIManager::InitMainHUD(APlayerController* Controller)
//{
//	CreateMainHUD(Controller);
//	// BindHealthToTarget(Controller->GetPawn());
//
//	// BindAmmoToUI(Controller->GetPawn()->GetEquippedWeapon();)
//}

void UUIManager::CreateMainHUD()
{
	if (!MainHUDClass) return;
	if (MainHUD) {
		MainHUD->RemoveFromParent();
		MainHUD = nullptr;
	}
	MainHUD = CreateWidget<UMainHUD>(OwningController.Get(), MainHUDClass);
	MainHUD->AddToViewport();

	// MainHUD->Init();
}


void UUIManager::BindHealthToTarget(UObject* Target)
{
	if (!MainHUD || !Target) return;

	//// DisConnect previous connected target
	//if (CurrentActor.IsValid())
	//   {
	//       if (CurrentActor->GetClass()->ImplementsInterface(UHealthProviderInterface::StaticClass()))
	//       {
	//           IHealthProviderInterface* OldInterface = Cast<IHealthProviderInterface>(CurrentActor.Get());
	//           if (OldInterface)
	//           {
	//               OldInterface->GetOnHealthChangedDelegate().RemoveDynamic(MainHUD, &UMainHUD::UpdateHealthBar);
	//           }
	//       }
	//   }
	/*if(TargetActor->Implements<UHealthProviderInterface>())*/
	// Check Has Interface
	//if (TargetActor->GetClass()->ImplementsInterface(UHealthProviderInterface::StaticClass()))
	//{

	if (CurrentHealthTarget.IsValid())
	{
		if (IHealthProviderInterface* OldProvider =
			Cast<IHealthProviderInterface>(CurrentHealthTarget.Get()))
		{
			OldProvider->GetHealthChangedDelegate()
				.RemoveDynamic(MainHUD, &UMainHUD::UpdateHealthBar);
		}
	}

	IHealthProviderInterface* Provider = Cast<IHealthProviderInterface>(Target);

	if (Provider)
	{
		Provider->GetHealthChangedDelegate().AddDynamic(MainHUD, &UMainHUD::UpdateHealthBar);

		CurrentHealthTarget = Target;

		float Cur = IHealthProviderInterface::Execute_GetCurrentHealth(Target);
		float Max = IHealthProviderInterface::Execute_GetMaxHealth(Target);

		MainHUD->UpdateHealthBar(Cur, Max);
	}
}

void UUIManager::BindAmmoToTarget(UObject* Target)
{

	// 1️⃣ 이전 Ammo 바인딩 해제
	if (CurrentAmmoTarget.IsValid())
	{
		if (IAmmoUIInterface* OldProvider =
			Cast<IAmmoUIInterface>(CurrentAmmoTarget.Get()))
		{
			OldProvider->GetAmmoChangedDelegate()
				.RemoveDynamic(MainHUD, &UMainHUD::UpdateAmmoText);
		}
	}

	IAmmoUIInterface* Provider = Cast<IAmmoUIInterface>(Target);
	if (Provider) 
	{
		Provider->GetAmmoChangedDelegate().AddDynamic(MainHUD, &UMainHUD::UpdateAmmoText);

		CurrentAmmoTarget = Target;

		int32 Cur = IAmmoUIInterface::Execute_GetCurrentAmmo(Target);
		int32 Max = IAmmoUIInterface::Execute_GetMaxAmmo(Target);

		MainHUD->UpdateAmmoText(Cur, Max);
	}
}

void UUIManager::BindStaminaToUI(UObject* Target)
{
	if (!MainHUD || !IsValid(Target)) return;


	if (CurrentStaminaTarget.IsValid())
	{
		if (IStaminaUIInterface* OldProvider =
			Cast<IStaminaUIInterface>(CurrentStaminaTarget.Get()))
		{
			OldProvider->GetStaminaChangedDelegate()
				.RemoveDynamic(MainHUD, &UMainHUD::UpdateStaminaBar);
		}
	}

	IStaminaUIInterface* Provider = Cast<IStaminaUIInterface>(Target);
	if (!Provider) return;

	Provider->GetStaminaChangedDelegate()
		.AddDynamic(MainHUD, &UMainHUD::UpdateStaminaBar);

	CurrentStaminaTarget = Target;

	float Cur = IStaminaUIInterface::Execute_GetCurrentStamina(Target);
	float Max = IStaminaUIInterface::Execute_GetMaxStamina(Target);

	MainHUD->UpdateStaminaBar(Cur, Max);
}

void UUIManager::BindMagazineToUI(UObject* Target)
{

	IMagazineInterface* Provider = Cast<IMagazineInterface>(Target);
	Provider->GetMagazineChangedDelegate()
		.AddDynamic(MainHUD, &UMainHUD::UpdateMagazineText);

	//UAmmoPickUpInterface* Provider = Cast<UAmmoPickUpInterface>(Target);
	//if (!Provider) return;

	//Provider->GetMagazineChangedDelegate()
	//	.AddDynamic(MainHUD, &UMainHUD::UpdateStaminaBar);

}



void UUIManager::RegisterUIObject(UObject* Target)
{
	if (!IsValid(Target))
	{
		UE_LOG(LogTemp, Warning, TEXT("RegisterUIObject: Invalid Target"));
		return;
	}

	if (Target->GetClass()->ImplementsInterface(UHealthProviderInterface::StaticClass()))
	{
		BindHealthToTarget(Target);
	}
	
	if (Target->Implements<UStaminaUIInterface>()) {
		BindStaminaToUI(Target);
	}

	// if(Target->Implements<UAmmoUIInterface>())
	if (Target->GetClass()->ImplementsInterface(UAmmoUIInterface::StaticClass()))
	{
		BindAmmoToTarget(Target);
		UE_LOG(LogTemp, Warning, TEXT("UIManager:: RegisterUIObject - AmmoUIInterface Implemented"));
	}

	if (Target->Implements<UMagazineInterface>())
	{
		BindMagazineToUI(Target);
	}

	//if (Target->Implements<UAmmoPickUpInterface>())
	//{
	//	BindMagazineToUI(Target);
	//}
}