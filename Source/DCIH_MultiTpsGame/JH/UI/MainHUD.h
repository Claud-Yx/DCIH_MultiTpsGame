#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/HealthProviderInterface.h"
#include "MainHUD.generated.h"

UCLASS()
class DCIH_MULTITPSGAME_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void Init();

	UFUNCTION()
	void UpdateHealthBar(float CurrentHealth, float MaxHealth);

	UFUNCTION()
	void UpdateAmmoText(int32 CurAmmo, int32 MaxAmmo);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHealthWidget> WBP_CharacterHealthWidget;

	UPROPERTY(meta =(BindWidget))
	TObjectPtr<class UAmmoWidget> WBP_AmmoWidget;
};