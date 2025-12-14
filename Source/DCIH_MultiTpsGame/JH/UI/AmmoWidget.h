// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmmoWidget.generated.h"

/**
 * 
 */
UCLASS()
class DCIH_MULTITPSGAME_API UAmmoWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_AmmoNum;

public:
	UFUNCTION()
	void Update(int32 CurrentAmmo, int32 MaxAmmo);
	
};
