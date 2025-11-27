#include "JH/UI/MainHUD.h"
#include "JH/UI/HealthWidget.h"
#include "JH/Components/HealthComponent.h"
#include "JH/UI/Interface/StatUpdatable.h"

void UMainHUD::Init()
{
	// OwnerCharacter = Cast<AJHCharacter>(GetOwningPlayer()->GetPawn());
	if (WBP_CharacterHealthWidget) {
		BindHealthComponentToUI();
	}
}

void UMainHUD::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
	if (WBP_CharacterHealthWidget)
	{
		WBP_CharacterHealthWidget->Update(CurrentHealth, MaxHealth);
	}
}

void UMainHUD::BindHealthComponentToUI()
{
	APawn* Pawn = GetOwningPlayerPawn();
	if (!Pawn) return;

	IStatUpdatable* StatObj = Cast<IStatUpdatable>(Pawn);
	if (!StatObj) return;

	UHealthComponent* HealthComp = StatObj->GetHealthComponent();
	if (!HealthComp) return;

	HealthComp->OnHealthChanged.AddDynamic(this, &UMainHUD::UpdateHealthBar);

	UpdateHealthBar(HealthComp->GetCurrentHealth(), HealthComp->GetMaxHealth());

}



// void UMainHUD::BindHealthComponentToUI()
// {
// 	if (!OwnerCharacter.IsValid()) return;
// 
// 	CachedHealthComp = OwnerCharacter->FindComponentByClass<UHealthComponent>();
// 
// 	if (CachedHealthComp.IsValid())
// 	{
// 		CachedHealthComp->OnHealthChanged.AddUniqueDynamic(this, &UMainHUD::UpdateHealthBar);
// 		UpdateHealthBar(CachedHealthComp->GetCurrentHealth(), CachedHealthComp->GetMaxHealth());
// 	}
// }



// void UMainHUD::UpdateHealthBar(float CurrentHealth, float MaxHealth)
// {
// 	if (WBP_CharacterHealthWidget)
// 	{
// 		WBP_CharacterHealthWidget->Update(CurrentHealth, MaxHealth);
// 	}
// }