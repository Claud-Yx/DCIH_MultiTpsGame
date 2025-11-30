#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/HealthProviderInterface.h"
#include "MainHUD.generated.h"

UCLASS()
class DCIH_MULTITPSGAME_API UMainHUD 
	: public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void Init();

	UFUNCTION()
	void UpdateHealthBar(float CurrentHealth, float MaxHealth);

	// UFUNCTION(BlueprintCallable, Category = "HUD")
	// void UpdateHealthBar(float CurrentHealth, float MaxHealth);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHealthWidget> WBP_CharacterHealthWidget;


private:
	UFUNCTION()
	void BindHealthComponentToUI();

	// UPROPERTY()
	// TWeakObjectPtr<class ACharacter> OwnerCharacter;
	   
	// UFUNCTION()
	// void BindHealthComponentToUI();
	   
	// UPROPERTY()
	// TWeakObjectPtr<class UHealthComponent> CachedHealthComp;
};