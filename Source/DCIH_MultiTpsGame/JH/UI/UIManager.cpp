#include "JH/UI/UIManager.h"
#include "GameFramework/PlayerController.h"
#include "JH/UI/MainHUD.h"
#include "JH/UI/Interface/HealthProviderInterface.h"
#include "JH/UI/Interface/AmmoUIInterface.h"

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

void UUIManager::BindHealthToTarget(AActor* TargetActor)
{
	if (!MainHUD || !TargetActor) return;

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

	IHealthProviderInterface* Provider = Cast<IHealthProviderInterface>(TargetActor);

	if (Provider) 
	{
		Provider->GetHealthChangedDelegate().AddDynamic(MainHUD, &UMainHUD::UpdateHealthBar);

		CurrentHealthTarget = TargetActor;

		float Cur = IHealthProviderInterface::Execute_GetCurrentHealth(TargetActor);
		float Max = IHealthProviderInterface::Execute_GetMaxHealth(TargetActor);

		MainHUD->UpdateHealthBar(Cur, Max);
	}
}

void UUIManager::BindAmmoToTarget(AActor* TargetActor)
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

	IAmmoUIInterface* Provider = Cast<IAmmoUIInterface>(TargetActor);
	if (Provider) 
	{
		Provider->GetAmmoChangedDelegate().AddDynamic(MainHUD, &UMainHUD::UpdateAmmoText);

		CurrentAmmoTarget = TargetActor;

		int32 Cur = IAmmoUIInterface::Execute_GetCurrentAmmo(TargetActor);
		int32 Max = IAmmoUIInterface::Execute_GetMaxAmmo(TargetActor);

		MainHUD->UpdateAmmoText(Cur, Max);
	}
}

void UUIManager::CreateMainHUD()
{
	if (!MainHUDClass) return;
	MainHUD = CreateWidget<UMainHUD>(OwningController.Get(), MainHUDClass);
	MainHUD->AddToViewport();

	// MainHUD->Init();
}

void UUIManager::RegisterUIObject(AActor* Target)
{
	if (Target->GetClass()->ImplementsInterface(UHealthProviderInterface::StaticClass()))
	{
		BindHealthToTarget(Target);
	}

	if (Target->GetClass()->ImplementsInterface(UAmmoUIInterface::StaticClass()))
	{
		BindAmmoToTarget(Target);
		UE_LOG(LogTemp, Warning, TEXT("UIManager:: RegisterUIObject - AmmoUIInterface Implemented"));
	}
}