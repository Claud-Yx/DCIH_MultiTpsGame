#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h" // AActor 대신 UObject
#include "UIManager.generated.h"

UCLASS(BlueprintType, Blueprintable)
class DCIH_MULTITPSGAME_API UUIManager : public UObject
{
	/// <summary>
	/// ActorComponent를 사용하는게 좋음
	/// BP와 연동을 위해
	/// </summary>
	
	GENERATED_BODY()
	
public:	
	UUIManager();

    void Init (APlayerController* Controller);

private:
	void InitMainHUD(APlayerController* Controller);

    UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UMainHUD> MainHUDClass;

    UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMainHUD> MainHUD;
};