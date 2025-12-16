#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UIManager.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), BlueprintType, Blueprintable)
class DCIH_MULTITPSGAME_API UUIManager : public UActorComponent
{
	
	GENERATED_BODY()
	
public:	
	UUIManager();
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "UI")
	void Init();
	void RegisterUIObject(UObject* Target);
	void CreateMainHUD();

private:
	// void InitMainHUD(class APlayerController* Controller);
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void BindHealthToTarget(UObject* Target);

	UFUNCTION()
	void BindAmmoToTarget(UObject* Target);

	void BindStaminaToUI(UObject* Target);

private:
	UPROPERTY()
	TWeakObjectPtr<APlayerController> OwningController;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UMainHUD> MainHUDClass;

    UPROPERTY()
	TObjectPtr<UMainHUD> MainHUD;

	UPROPERTY()
	TWeakObjectPtr<AActor> CurrentActor;

private:
	TWeakObjectPtr<UObject> CurrentHealthTarget;
	TWeakObjectPtr<UObject> CurrentAmmoTarget;
	TWeakObjectPtr<UObject> CurrentStaminaTarget;
};