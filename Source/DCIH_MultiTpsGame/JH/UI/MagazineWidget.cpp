// Fill out your copyright notice in the Description page of Project Settings.


#include "JH/UI/MagazineWidget.h"
#include "Components/TextBlock.h"

void UMagazineWidget::NativeConstruct()
{
}

void UMagazineWidget::Update(int32 MagazineNum)
{
	if (!Text_MagazineNum) return;
	FString MagazineString = FString::Printf(TEXT("%d"), MagazineNum);

	Text_MagazineNum->SetText(FText::FromString(MagazineString));

}