#include "JH/Weapon/Rifle.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ARifle::ARifle()
{
	Damage = 30.f;
	TraceRange = 20000.f;
	MuzzleSocketName = TEXT("Muzzle");
	TraceChannel = ECC_Visibility;
}

void ARifle::Fire()
{
	if (!CanFire())
	{
		Reload();
		return;
	}

	// 발사 방향 계산
	FVector MuzzleLoc, TraceEnd;
	const FVector ShotDir = GetShotDirection(MuzzleLoc, TraceEnd);

	// 라인트레이스
	FHitResult Hit;
	const bool bHit = TraceBullet(MuzzleLoc, TraceEnd, Hit);

	// 디버그 선 그리기
	const FVector DebugEnd = bHit ? Hit.ImpactPoint : TraceEnd;
	DrawFireDebug(MuzzleLoc, DebugEnd, bHit, DebugEnd);

	// 데미지 적용
	if (bHit)
	{
		ApplyHitDamage(Hit, ShotDir);
	}

	// 탄 소모
	Ammo = FMath::Max(Ammo - 1, 0);
}

bool ARifle::TraceBullet(const FVector& MuzzleLoc, const FVector& TraceEnd, FHitResult& OutHit) const
{
	FCollisionQueryParams Params(SCENE_QUERY_STAT(RifleTrace), false, this);
	if (APawn* P = OwningPawn.Get()) Params.AddIgnoredActor(P);
	if (Mesh) Params.AddIgnoredComponent(Mesh);

	return GetWorld()->LineTraceSingleByChannel(
		OutHit,
		MuzzleLoc,
		TraceEnd,
		TraceChannel,
		Params
	);
}

void ARifle::ApplyHitDamage(const FHitResult& Hit, const FVector& ShotDir)
{
	if (Hit.GetActor())
	{
		UGameplayStatics::ApplyPointDamage(
			Hit.GetActor(),
			Damage,
			ShotDir,
			Hit,
			OwningPawn.IsValid() ? OwningPawn->GetController() : nullptr,
			this,
			UDamageType::StaticClass()
		);
	}
}

void ARifle::DrawFireDebug(const FVector& Start, const FVector& End, bool bHit, const FVector& HitLocation) const
{
	DrawDebugLine(GetWorld(), Start, End, FColor::Cyan, false, 3.f, 0, 1.5f);

	if (bHit)
	{
		DrawDebugPoint(GetWorld(), HitLocation, 10.f, FColor::Red, false, 2.f);
	}
}
