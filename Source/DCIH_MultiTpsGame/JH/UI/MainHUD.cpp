#include "JH/UI/MainHUD.h"
#include "JH/UI/HealthWidget.h"
#include "JH/Character/JHCharacter.h"
#include "JH/Components/HealthComponent.h"

void UMainHUD::Init()
{
	OwnerCharacter = Cast<AJHCharacter>(GetOwningPlayer()->GetPawn());
	BindHealthComponentToUI();
}



void UMainHUD::BindHealthComponentToUI()
{
	if (!OwnerCharacter.IsValid()) return;

	CachedHealthComp = OwnerCharacter->FindComponentByClass<UHealthComponent>();

	if (CachedHealthComp.IsValid())
	{
		CachedHealthComp->OnHealthChanged.AddUniqueDynamic(this, &UMainHUD::UpdateHealthBar);
		UpdateHealthBar(CachedHealthComp->GetCurrentHealth(), CachedHealthComp->GetMaxHealth());
	}
}



void UMainHUD::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
	if (WBP_CharacterHealthWidget)
	{
		WBP_CharacterHealthWidget->Update(CurrentHealth, MaxHealth);
	}
}