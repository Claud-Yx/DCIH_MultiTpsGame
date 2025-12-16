// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StaminaWidget.generated.h"

UCLASS()
class DCIH_MULTITPSGAME_API UStaminaWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Update(float Current, float Max);

private:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar>PB_StaminaBar;

};
