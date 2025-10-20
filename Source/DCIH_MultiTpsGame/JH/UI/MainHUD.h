#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

class UHealthWidget;

UCLASS()
class DCIH_MULTITPSGAME_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateHealthBar(float CurrentHealth, float MaxHealth);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHealthWidget> WBP_CharacterHealthWidget;

	//UPROPERTY(meta = (BindWidget))
	//TObjectPtr<class UStaminaWidget> WBP_StaminaWidget
};