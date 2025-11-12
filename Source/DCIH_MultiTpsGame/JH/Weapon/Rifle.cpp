#include "JH/Weapon/Rifle.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"        

ARifle::ARifle()
{
    TraceRange = 20000.f;

    CurAmmo = 300;
    MaxAmmo = 30;
    Damage = 30.f;
    FireRate = 0.1f;
    LastFireTime = -FireRate; // 처음엔 바로 발사 가능하도록 초기화
    ReloadTime = 1.0f;

	RecoilConfig.RecoilVerticalMin = 0.05f;
	RecoilConfig.RecoilVerticalMax = 0.2f;
	RecoilConfig.RecoilHorizontalMin = -0.1f;
	RecoilConfig.RecoilHorizontalMax = 0.1f;
	RecoilConfig.RecoilRecoverySpeed = 1.f;
}

void ARifle::Tick(float Deltatime)
{
    Super::Tick(Deltatime);
}

// 프레임 2개씩 들어오는데
// 첫 조건 통과하고 쏘고
// 위의 건 통과 못하고 밑에만 통과해서 쏘는 경우가 있음
void ARifle::Fire()
{
	if (!CanFire()) return;

	if (CurAmmo <= 0)
	{
		Reload();
		return;
	}

	float currentTime = GetWorld()->GetTimeSeconds();

	if (currentTime - LastFireTime < FireRate)
	{
		return;
	}

	LastFireTime = currentTime; // 마지막 발사 시간 업데이트

    Super::Fire();

    //const FVector MuzzleLoc = GetMuzzleLocation();
    //const FVector AimPoint = GetAimPoint();

    //// 그냥 시각화만 해줌 (부모에서 이미 계산해준 값 이용)
    //DrawDebugLine(GetWorld(), MuzzleLoc, AimPoint, FColor::Cyan, false, 2.f, 0, 1.5f);
    //DrawDebugPoint(GetWorld(), AimPoint, 10.f, FColor::Red, false, 2.f);




    const FVector MuzzleLoc = GetMuzzleLocation();
    const FVector AimPoint = GetAimPoint();

    const FVector ShotDir = (AimPoint - MuzzleLoc).GetSafeNormal();

    FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(RifleTrace), true, this);

    if (OwnerCharacter.IsValid())
    {
        TraceParams.AddIgnoredActor(OwnerCharacter.Get());
    }

    if (MeshComp)
    {
        TraceParams.AddIgnoredComponent(MeshComp.Get());
    }
    FHitResult Hit;
    const bool bHit = GetWorld()->LineTraceSingleByChannel(
        Hit,
        MuzzleLoc,
        AimPoint,
        TraceChannel,
        TraceParams
    );



    DrawDebugLine(GetWorld(), MuzzleLoc, AimPoint, FColor::Cyan, false, 2.f, 0, 1.5f);


    if (bHit && Hit.bBlockingHit)
    {
        DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 8.f, FColor::Red, false, 2.f);

        ApplyDamage(Hit, ShotDir);
    }
    else
    {
        DrawDebugPoint(GetWorld(), AimPoint, 6.f, FColor::Blue, false, 2.f);
    }
}