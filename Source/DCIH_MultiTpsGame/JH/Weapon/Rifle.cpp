#include "JH/Weapon/Rifle.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ARifle::ARifle()
{
    TraceRange = 20000.f;

    CurAmmo = 30;
    MaxAmmo = 30;
    Damage = 30.f;
    FireRate = 0.3f;
    LastFireTime = -FireRate; // 처음엔 바로 발사 가능하도록 초기화
    ReloadTime = 2.0f;
}

void ARifle::Fire()
{
    if (!CanFire()) return;
    Super::Fire();


    float currentTime = GetWorld()->GetTimeSeconds();

    if (currentTime - LastFireTime < FireRate)
    {
        return;
    }

    LastFireTime = currentTime; // 마지막 발사 시간 업데이트

    const FVector MuzzleLoc = GetMuzzleLocation();
    const FVector AimPoint = GetAimPoint();

    // 그냥 시각화만 해줌 (부모에서 이미 계산해준 값 이용)
    DrawDebugLine(GetWorld(), MuzzleLoc, AimPoint, FColor::Cyan, false, 2.f, 0, 1.5f);
    DrawDebugPoint(GetWorld(), AimPoint, 10.f, FColor::Red, false, 2.f);

    CurAmmo = FMath::Max(CurAmmo - 1, 0);
}