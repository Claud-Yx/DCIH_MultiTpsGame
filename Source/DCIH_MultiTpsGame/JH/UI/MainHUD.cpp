#include "JH/UI/MainHUD.h"
#include "JH/UI/HealthWidget.h"

void UMainHUD::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
	if (WBP_CharacterHealthWidget)
	{
		WBP_CharacterHealthWidget->UpdateHealthBar(CurrentHealth, MaxHealth);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HealthWidget is nullptr in MainHUD!"));
	}
}