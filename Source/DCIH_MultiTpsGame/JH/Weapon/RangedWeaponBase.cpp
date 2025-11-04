#include "JH/Weapon/RangedWeaponBase.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"



ARangedWeaponBase::ARangedWeaponBase()
{
	MuzzleSocketName = "Muzzle";
	TraceChannel = ECC_Visibility;
}

void ARangedWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

FVector ARangedWeaponBase::GetMuzzleLocation() const
{
	if (MeshComp && MeshComp->DoesSocketExist(MuzzleSocketName))
	{
		return MeshComp->GetSocketLocation(MuzzleSocketName);
	}
	return GetActorLocation();
}

FVector ARangedWeaponBase::GetAimPoint() const
{
	FVector camStartLoc;
	FRotator camRot;

	OwnerCharacter.Get()->GetController()->GetPlayerViewPoint(camStartLoc, camRot);

	if (const ACharacter* P = OwnerCharacter.Get())
	{
		if (AController* C = P->GetController())
		{
			C->GetPlayerViewPoint(camStartLoc, camRot);
		}
	}
	const FVector camEndLoc = camStartLoc + camRot.Vector() * TraceRange;



	FHitResult camHit;
	FCollisionQueryParams camParams(SCENE_QUERY_STAT(CameraAimTrace), false, this);
	if (APawn* P = OwnerCharacter.Get())
	{
		camParams.AddIgnoredActor(P);
	}
	if (MeshComp)
	{
		camParams.AddIgnoredComponent(Cast<UPrimitiveComponent>(MeshComp));
	}

	if (GetWorld()->LineTraceSingleByChannel
	(
		camHit,
		camStartLoc,
		camEndLoc,
		TraceChannel,
		camParams) 
		&& camHit.bBlockingHit)
	{
		return camHit.ImpactPoint;
	}
	return camEndLoc;
}

bool ARangedWeaponBase::CanFire() const
{
	return 
		(WeaponState == EWeaponState::Equipping || WeaponState == EWeaponState::Firing) ;
}

void ARangedWeaponBase::Fire()
{
	if(CurAmmo<=0)
	{
		Reload();
		return;
	}
	ApplyRecoil();
	CurAmmo = FMath::Max(CurAmmo - 1, 0);

}

void ARangedWeaponBase::Reload()
{
	if (GetWeaponState() == EWeaponState::Reloading)
		return;
	
	SetWeaponState(EWeaponState::Reloading);

	GetWorld()->GetTimerManager().SetTimer(
		ReloadTimerHandle,
		this,
		&ARangedWeaponBase::FinishReload,
		ReloadTime,
		false
	);
}

void ARangedWeaponBase::FinishReload()
{
	CurAmmo = MaxAmmo;
	SetWeaponState(EWeaponState::Equipping);

	//if (UWorld* World = GetWorld())
	//{
	//	World->GetTimerManager().ClearTimer(ReloadTimerHandle);
	//}
}

void ARangedWeaponBase::ApplyRecoil()
{
	if (APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetController()))
	{
		if (RecoilShake)
		{
			PC->ClientStartCameraShake(RecoilShake);
		}
		else
		{
			// 간단한 반동 입력
			PC->AddPitchInput(FMath::FRandRange(-1.5f, -3.0f));
			PC->AddYawInput(FMath::FRandRange(-0.5f, 0.5f));
		}
	}
}


//// 인자 없이 그냥
//FVector ARangedWeaponBase::GetShotDirection() const
//{
//	return (GetAimPoint() - GetMuzzleLocation()).GetSafeNormal();
//}