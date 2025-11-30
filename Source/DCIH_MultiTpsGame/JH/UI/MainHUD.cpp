#include "JH/UI/MainHUD.h"
#include "JH/UI/HealthWidget.h"
// #include "JH/Components/HealthComponent.h"
#include "JH/UI/Interface/HealthProviderInterface.h"
#include "Kismet/KismetSystemLibrary.h"      // PrintString

void UMainHUD::Init()
{
	// OwnerCharacter = Cast<AJHCharacter>(GetOwningPlayer()->GetPawn());
	//if (WBP_CharacterHealthWidget) {
	BindHealthComponentToUI();
	//}
}

void UMainHUD::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
	//if (WBP_CharacterHealthWidget)
	//{
	WBP_CharacterHealthWidget->Update(CurrentHealth, MaxHealth);
	//}

	UKismetSystemLibrary::PrintString(this, TEXT("Execute4"));

}

void UMainHUD::BindHealthComponentToUI()
{
	//APawn* Pawn = GetOwningPlayerPawn();

	//Pawn->GetClass()->ImplementsInterface(UHealthProviderInterface::StaticClass());

	//UHealthComponent * HealthComp = IHealthProviderInterface::Execute_GetHealthComponent(Pawn);

	//HealthComp->OnHealthChanged.AddDynamic(this, &UMainHUD::UpdateHealthBar);

	//UpdateHealthBar(HealthComp->GetCurrentHealth(), HealthComp->GetMaxHealth());



	// APawn* Pawn = GetOwningPlayerPawn();
	// if (!Pawn) return;
	   
	// if (!Pawn->GetClass()->ImplementsInterface(UHealthProviderInterface::StaticClass()))
	// 	return;
	   
	// // 인터페이스 이벤트 구독
	// IHealthProviderInterface::Execute_GetOnHealthChangedDelegate(Pawn)
	// 	.AddDynamic(this, &UMainHUD::UpdateHealthBar);
	   
	// // 초기 업데이트
	// UpdateHealthBar(
	// 	IHealthProviderInterface::Execute_GetCurrentHealth(Pawn),
	// 	IHealthProviderInterface::Execute_GetMaxHealth(Pawn)
	// );

	APawn* Pawn = GetOwningPlayerPawn();

	Pawn->GetClass()->ImplementsInterface(UHealthProviderInterface::StaticClass());
	

	IHealthProviderInterface* HealthProvider = Cast<IHealthProviderInterface>(Pawn);

	FOnProviderHealthChanged& HealthDelegate = HealthProvider->GetOnHealthChangedDelegate();

	HealthDelegate.AddDynamic(this, &UMainHUD::UpdateHealthBar);

	float CurrentHealth = HealthProvider->Execute_GetCurrentHealth(Pawn);
	float MaxHealth = HealthProvider->Execute_GetMaxHealth(Pawn);

	UpdateHealthBar(CurrentHealth, MaxHealth);





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