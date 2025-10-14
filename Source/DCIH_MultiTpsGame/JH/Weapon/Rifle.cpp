#include "JH/Weapon/Rifle.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ARifle::ARifle()
{
	// 블루프린트에서 하는게 나음
	damage = 30.f;
	traceRange = 20000.f;
	muzzleSocketName = TEXT("Muzzle");
	traceChannel = ECC_Visibility;
    fireRate = 0.3f;
    lastFireTime = -fireRate; // 처음엔 바로 발사 가능하도록 초기화

}

void ARifle::Fire()
{
    //if (!CanFire())
    //{
    //    Reload();
    //    return;
    //}
    // 현재 시간 가져오기
    float currentTime = GetWorld()->GetTimeSeconds();

    if (currentTime - lastFireTime < fireRate)
    {
        return;
    }

    lastFireTime = currentTime; // 마지막 발사 시간 업데이트
	Super::Fire();

    UE_LOG(LogTemp, Warning, TEXT("rifle"));


    const FVector MuzzleLoc = GetMuzzleLocation();
    const FVector AimPoint = GetAimPoint();

    // 그냥 시각화만 해줌 (부모에서 이미 계산해준 값 이용)
    DrawDebugLine(GetWorld(), MuzzleLoc, AimPoint, FColor::Cyan, false, 2.f, 0, 1.5f);
    DrawDebugPoint(GetWorld(), AimPoint, 10.f, FColor::Red, false, 2.f);

    curAmmo = FMath::Max(curAmmo - 1, 0);
}

//bool ARifle::TraceBullet(const FVector& MuzzleLoc, const FVector& TraceEnd, FHitResult& OutHit) const
//{
//	FCollisionQueryParams Params(SCENE_QUERY_STAT(RifleTrace), false, this);
//	if (APawn* P = OwningPawn.Get()) Params.AddIgnoredActor(P);
//	if (Mesh) Params.AddIgnoredComponent(Mesh);
//
//	return GetWorld()->LineTraceSingleByChannel(
//		OutHit,
//		MuzzleLoc,
//		TraceEnd,
//		TraceChannel,
//		Params
//	);
//}

//void ARifle::ApplyHitDamage(const FHitResult& Hit, const FVector& ShotDir)
//{
//	if (Hit.GetActor())
//	{
//		// UGameplayStatics::ApplyDamage{}
//
//		UGameplayStatics::ApplyPointDamage(
//			Hit.GetActor(),
//			Damage,
//			ShotDir,
//			Hit,
//			OwningPawn.IsValid() ? OwningPawn->GetController() : nullptr,
//			this,
//			UDamageType::StaticClass()
//		);
//	}
//}

//void ARifle::DrawFireDebug(const FVector& Start, const FVector& End, bool bHit, const FVector& HitLocation) const
//{
//	DrawDebugLine(GetWorld(), Start, End, FColor::Cyan, false, 3.f, 0, 1.5f);
//
//	if (bHit)
//	{
//		DrawDebugPoint(GetWorld(), HitLocation, 10.f, FColor::Red, false, 2.f);
//	}
//}
