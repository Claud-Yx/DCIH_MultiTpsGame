#include "JH/UI/MainHUD.h"
#include "JH/UI/HealthWidget.h"
#include "JH/UI/AmmoWidget.h"
#include "JH/UI/Interface/HealthProviderInterface.h"

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