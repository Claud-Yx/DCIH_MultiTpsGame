#include "JH/Weapon/Rifle.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

ARifle::ARifle()
{
 //   TraceRange = 20000.f;

 //   CurAmmo = 300;
 //   MaxAmmo = 30;
 //   Damage = 30.f;
 //   FireRate = 0.1f;
 //   LastFireTime = -FireRate; // 처음엔 바로 발사 가능하도록 초기화
 //   ReloadTime = 1.0f;

	//RecoilConfig.RecoilVerticalMin = 0.05f;
	//RecoilConfig.RecoilVerticalMax = 0.2f;
	//RecoilConfig.RecoilHorizontalMin = -0.1f;
	//RecoilConfig.RecoilHorizontalMax = 0.1f;
	//RecoilConfig.RecoilRecoverySpeed = 1.f;
}

// 프레임 2개씩 들어오는데
// 첫 조건 통과하고 쏘고
// 위의 건 통과 못하고 밑에만 통과해서 쏘는 경우가 있음
void ARifle::Fire()
{
    Super::Fire();

    // if (!bLastFireSuccess) return;

	HitScan();
}

void ARifle::HitScan()
{
    FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(RifleTrace), true, this);

	TraceParams.AddIgnoredActor(this);

    if (OwnerCharacter.IsValid()) TraceParams.AddIgnoredActor(OwnerCharacter.Get());


	const FVector Start = GetMuzzleLocation();
    const FVector End = GetAimPoint();



    if (MeshComp)
    {
        TraceParams.AddIgnoredComponent(MeshComp.Get());
    }

    FHitResult Hit;
    const bool bHit = GetWorld()->LineTraceSingleByChannel(
        Hit,
        Start,
        End,
        ECC_Visibility,
        TraceParams
    );



    if (bHit) {
        const FVector ShotDir = (End - Start).GetSafeNormal();
        ApplyHitDamage(Hit, ShotDir);
    }

	DrawDebugTrace(Start, End, Hit, bHit);
}

//void ARifle::DrawDebugTrace(const FVector& ShotDir, const FHitResult& Hit, const bool bHit) const
//{
//
//    DrawDebugLine(GetWorld(), GetMuzzleLocation(), GetAimPoint(), FColor::Green, false, 2.f, 0, 1.5f);
//
//    if (bHit && Hit.bBlockingHit)
//    {
//        DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 8.f, FColor::Red, false, 2.f);
//    }
//    else
//    {
//        DrawDebugPoint(GetWorld(), GetAimPoint(), 6.f, FColor::Blue, false, 2.f);
//    }
//}