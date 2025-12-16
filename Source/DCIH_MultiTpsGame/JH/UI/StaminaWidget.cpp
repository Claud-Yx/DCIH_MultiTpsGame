// Fill out your copyright notice in the Description page of Project Settings.


#include "JH/UI/StaminaWidget.h"
#include "Components/ProgressBar.h"

void UStaminaWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (PB_StaminaBar)
	{
		PB_StaminaBar->SetPercent(1.f);
	}
}

void UStaminaWidget::Update(float Current, float Max)
{
	if (!PB_StaminaBar || Max <= 0.f) return;

	PB_StaminaBar->SetPercent(Current/Max);
}


