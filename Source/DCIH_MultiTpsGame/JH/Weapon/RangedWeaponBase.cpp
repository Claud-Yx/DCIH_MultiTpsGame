#include "JH/Weapon/RangedWeaponBase.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"

ARangedWeaponBase::ARangedWeaponBase()
{
	if (Ammo > MaxAmmo)
	{
		Ammo = MaxAmmo;
	}
}

void ARangedWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

bool ARangedWeaponBase::CanFire() const
{
	const bool bPawnValid = OwningPawn.IsValid();
	return !(GetWeaponState() == EWeaponState::Reloading) && Ammo > 0 && bPawnValid;
}

void ARangedWeaponBase::Fire()
{
}

void ARangedWeaponBase::Reload()
{
	if (GetWeaponState() == EWeaponState::Reloading || Ammo >= MaxAmmo)
	{
		return;
	}

	SetWeaponState(EWeaponState::Reloading);

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			ReloadTimerHandle,
			this,
			&ARangedWeaponBase::FinishReload,
			ReloadTime,
			false
		);
	}
	else
	{
		FinishReload();
	}
}

void ARangedWeaponBase::FinishReload()
{
	Ammo = MaxAmmo;
	SetWeaponState(EWeaponState::Idle);

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ReloadTimerHandle);
	}
}

FVector ARangedWeaponBase::GetMuzzleLocation() const
{
	if (Mesh && Mesh->DoesSocketExist(MuzzleSocketName))
	{
		return Mesh->GetSocketLocation(MuzzleSocketName);
	}
	return GetActorLocation();
}

FVector ARangedWeaponBase::GetAimPoint() const
{
	FVector CamStart = GetActorLocation();
	FRotator CamRot = GetActorRotation();

	if (APawn* P = OwningPawn.Get())
	{
		if (AController* C = P->GetController())
		{
			C->GetPlayerViewPoint(CamStart, CamRot);
		}
	}
	const FVector CamEnd = CamStart + CamRot.Vector() * TraceRange;


	
	FHitResult CamHit;
	FCollisionQueryParams CamParams(SCENE_QUERY_STAT(CameraAimTrace), false, this);
	if (APawn* P = OwningPawn.Get()) CamParams.AddIgnoredActor(P);
	if (Mesh) CamParams.AddIgnoredComponent(Mesh);

	if (GetWorld()->LineTraceSingleByChannel(CamHit, CamStart, CamEnd, TraceChannel, CamParams) && CamHit.bBlockingHit)
	{
		return CamHit.ImpactPoint;
	}
	return CamEnd;
}

FVector ARangedWeaponBase::GetShotDirection(FVector& OutMuzzleLoc, FVector& OutTraceEnd) const
{
	const FVector AimPoint = GetAimPoint();
	OutMuzzleLoc = GetMuzzleLocation();

	FVector ShotDir = (AimPoint - OutMuzzleLoc).GetSafeNormal();
	OutTraceEnd = OutMuzzleLoc + ShotDir * TraceRange;
	return ShotDir;
}

