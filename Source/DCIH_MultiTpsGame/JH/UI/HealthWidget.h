#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

UCLASS()
class DCIH_MULTITPSGAME_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeConstruct() override;

private:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UProgressBar>PB_HealthBar;

public:
    UFUNCTION()
    void Update(float Current, float Max);
	
};
