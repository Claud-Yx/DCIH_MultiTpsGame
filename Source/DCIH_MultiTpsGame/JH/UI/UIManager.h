#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h" // AActor ´ë½Å UObject
#include "UIManager.generated.h"

UCLASS(BlueprintType, Blueprintable)
class DCIH_MULTITPSGAME_API UUIManager : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UUIManager();

    void Init (APlayerController* Controller);

	void InitMainHUD(APlayerController* Controller);

	UFUNCTION(BlueprintCallable, Category = "UI")
    void OnHealthChanged(float Current, float Max);

    //void OnAmmoChanged(int32 CurrentAmmo, int32 MaxAmmo);

    //UFUNCTION(BlueprintCallable, Category = "UI")
    //void ToggleInventory();

private:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TWeakObjectPtr<APlayerController> OwningPlayerController;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UMainHUD> MainHUDClass;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMainHUD> MainHUD;
};