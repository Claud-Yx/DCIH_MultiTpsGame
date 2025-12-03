#include "JH/UI/UIManager.h"
#include "JH/UI/MainHUD.h"
#include "JH/UI/Interface/HealthProviderInterface.h"

UUIManager::UUIManager()
{

}

void UUIManager::Init(APlayerController* Controller)
{
	InitMainHUD(Controller);

	if (Controller)
	{
		BindHealthToTarget(Controller->GetPawn());	// ÀÌÁ¤µµ?
	}
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



	// Check Has Interface
	if (TargetActor->GetClass()->ImplementsInterface(UHealthProviderInterface::StaticClass()))
	{
		IHealthProviderInterface* Provider = Cast<IHealthProviderInterface>(TargetActor);

		if (Provider) {
			Provider->GetHealthChangedDelegate().AddDynamic(MainHUD, &UMainHUD::UpdateHealthBar);

			float Cur = IHealthProviderInterface::Execute_GetCurrentHealth(TargetActor);
			float Max = IHealthProviderInterface::Execute_GetMaxHealth(TargetActor);

			MainHUD->UpdateHealthBar(Cur, Max);
		}
	}
}

void UUIManager::InitMainHUD(APlayerController* Controller)
{
    if (!MainHUDClass) return;
    MainHUD = CreateWidget<UMainHUD>(Controller, MainHUDClass);
	MainHUD->AddToViewport();

	// MainHUD->Init();
}