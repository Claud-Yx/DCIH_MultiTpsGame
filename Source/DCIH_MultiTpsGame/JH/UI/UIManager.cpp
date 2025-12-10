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
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	if (PC)
	{
		InitMainHUD(PC);

	}
}


void UUIManager::InitMainHUD(APlayerController* Controller)
{
	CreateMainHUD(Controller);
	BindHealthToTarget(Controller->GetPawn());

	BindAmmoToUI(Controller->GetPawn()->GetEquippedWeapon();)
}

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
	if (TargetActor->GetClass()->ImplementsInterface(UHealthProviderInterface::StaticClass()))
	{
		IHealthProviderInterface* Provider = Cast<IHealthProviderInterface>(TargetActor);

		if (Provider) {
			// 주의 : 바인딩 제거 해야함
			Provider->GetHealthChangedDelegate().AddDynamic(MainHUD, &UMainHUD::UpdateHealthBar);

			float Cur = IHealthProviderInterface::Execute_GetCurrentHealth(TargetActor);
			float Max = IHealthProviderInterface::Execute_GetMaxHealth(TargetActor);

			MainHUD->UpdateHealthBar(Cur, Max);
		}
	}
}

void UUIManager::BindAmmoToUI(AActor* TargetActor)
{
	if (TargetActor->GetClass()->ImplementsInterface(UAmmoUIInterface::StaticClass()))
	{
		IAmmoUIInterface* Provider = Cast<IAmmoUIInterface>(TargetActor);
		if (Provider) {
			// 주의 : 바인딩 제거 해야함
			Provider->GetAmmoChangedDelegate().AddDynamic(MainHUD, &UMainHUD::);
			int32 Cur = IAmmoUIInterface::Execute_GetCurrentAmmo(TargetActor);
			int32 Max = IAmmoUIInterface::Execute_GetMaxAmmo(TargetActor);
			// MainHUD->UpdateAmmo(Cur, Max);
		}
	}
}

void UUIManager::CreateMainHUD(APlayerController* Controller)
{
    if (!MainHUDClass) return;
    MainHUD = CreateWidget<UMainHUD>(Controller, MainHUDClass);
	MainHUD->AddToViewport();

	// MainHUD->Init();
}