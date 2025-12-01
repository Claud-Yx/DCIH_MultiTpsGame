#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h" // AActor ��� UObject
#include "UIManager.generated.h"

UCLASS(BlueprintType, Blueprintable)
class DCIH_MULTITPSGAME_API UUIManager : public UObject
{
	
	GENERATED_BODY()
	
public:	
	UUIManager();

    void Init (APlayerController* Controller);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void BindHealthToTarget(AActor* TargetActor);
	
private:
	void InitMainHUD(APlayerController* Controller);

    UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UMainHUD> MainHUDClass;

    UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMainHUD> MainHUD;

	UPROPERTY()
	TWeakObjectPtr<AActor> CurrentActor;
};