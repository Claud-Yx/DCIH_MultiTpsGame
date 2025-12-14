// Fill out your copyright notice in the Description page of Project Settings.


#include "JH/UI/AmmoWidget.h"
#include "Components/TextBlock.h"

void UAmmoWidget::NativeConstruct()
{
}

void UAmmoWidget::Update(int32 CurrentAmmo, int32 MaxAmmo)
{
	if (!Text_AmmoNum) return;
	FString AmmoString = FString::Printf(TEXT("%d / %d"), CurrentAmmo, MaxAmmo);
	Text_AmmoNum->SetText(FText::FromString(AmmoString));
}