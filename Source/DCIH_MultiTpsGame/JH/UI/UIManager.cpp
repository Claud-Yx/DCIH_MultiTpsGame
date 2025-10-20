#include "JH/UI/UIManager.h"
#include "JH/UI/HealthWidget.h"
#include "JH/UI/MainHUD.h"
#include "JH/Character/JHCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UUIManager::UUIManager()
{

}

void UUIManager::Init(APlayerController* Controller)
{
	InitMainHUD(Controller);
}

void UUIManager::InitMainHUD(APlayerController* Controller)
{
    if (!MainHUDClass) return;
    MainHUD = CreateWidget<UMainHUD>(Controller, MainHUDClass);
	MainHUD->AddToViewport();
}



void UUIManager::OnHealthChanged(float Current, float Max)
{
    MainHUD->UpdateHealthBar(Current, Max);
}

//void UUIManager::OnSatminaChanged(float Current, float Max)
//{
//	//MainHUD->UpdateStaminaBar(Current, Max);
//}
