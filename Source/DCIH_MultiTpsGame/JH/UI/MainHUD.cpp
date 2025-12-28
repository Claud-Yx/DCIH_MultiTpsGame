#include "JH/UI/MainHUD.h"
#include "JH/UI/HealthWidget.h"
#include "JH/UI/AmmoWidget.h"
#include "JH/UI/Interface/HealthProviderInterface.h"
#include "JH/UI/StaminaWidget.h"
#include "JH/UI/MagazineWidget.h"


void UMainHUD::Init()
{
}

void UMainHUD::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
	if (WBP_CharacterHealthWidget)
	{
		WBP_CharacterHealthWidget->Update(CurrentHealth, MaxHealth);
	}
}

void UMainHUD::UpdateAmmoText(int32 CurAmmo, int32 MaxAmmo)
{
	if (WBP_AmmoWidget)
	{
		WBP_AmmoWidget->Update(CurAmmo, MaxAmmo);
	}
}

void UMainHUD::UpdateStaminaBar(float Current, float Max)
{
	if (WBP_StaminaWidget) 
	{
		WBP_StaminaWidget->Update(Current, Max);
	}
}

 void UMainHUD::UpdateMagazineText(int32 MagazineNum)
 {
 	if (WBP_MagazineWidget)
 	{
 		WBP_MagazineWidget->Update(MagazineNum);
 	}
 }
