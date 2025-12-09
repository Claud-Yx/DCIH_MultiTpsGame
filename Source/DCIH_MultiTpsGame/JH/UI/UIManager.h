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

private:
	void InitMainHUD(class APlayerController* Controller);
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void BindHealthToTarget(AActor* TargetActor);

	void CreateMainHUD(APlayerController* Controller);

private:
	UPROPERTY()
	TWeakObjectPtr<APlayerController> OwningController;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UMainHUD> MainHUDClass;

    UPROPERTY()
	TObjectPtr<UMainHUD> MainHUD;

	UPROPERTY()
	TWeakObjectPtr<AActor> CurrentActor;
};