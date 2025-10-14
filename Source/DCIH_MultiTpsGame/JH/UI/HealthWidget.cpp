#include "JH/UI/HealthWidget.h"
#include "Components/ProgressBar.h"

void UHealthWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (PB_HealthBar)
    {
        PB_HealthBar->SetPercent(1.0f);
    }
}

void UHealthWidget::UpdateHealthBar(float Current, float Max)
{
    if (!PB_HealthBar || Max <= 0.f) return;

    PB_HealthBar->SetPercent(Current / Max);
}