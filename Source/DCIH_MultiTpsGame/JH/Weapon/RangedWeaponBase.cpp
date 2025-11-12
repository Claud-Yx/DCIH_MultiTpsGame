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
	PrimaryActorTick.bCanEverTick = true;

	MuzzleSocketName = "Muzzle";
	TraceChannel = ECC_Visibility;
}

void ARangedWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(true);



	//// 초기 Pitch 값 설정
	//if (OwnerCharacter.IsValid())
	//{
	//	LastControlPitch 
	//		= OwnerController->GetControlRotation().Pitch;
	//}
}

void ARangedWeaponBase::Tick(float DeltaTime)
{
	RecoilRecovery(DeltaTime);
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

	OwnerController->GetPlayerViewPoint(camStartLoc, camRot);

	/*if (const ACharacter* P = OwnerCharacter.Get())
	{
		if (AController* C = P->GetController())
		{
			C->GetPlayerViewPoint(camStartLoc, camRot);
		}
	}*/
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

bool ARangedWeaponBase::CanFire()
{
	if (WeaponState != EWeaponState::Equipping &&
		WeaponState != EWeaponState::Firing)
	{
		return false;
	}

	//const float CurrentTime = GetWorld()->GetTimeSeconds();
	//const float Elapsed = CurrentTime - LastFireTime;

	//if (Elapsed < FireRate)
	//{
	//	return false;
	//}

	return true;

}

void ARangedWeaponBase::Fire()
{
	//if (!CanFire()) return;

	//if (CurAmmo <= 0)
	//{
	//	Reload();
	//	return;
	//}

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

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ReloadTimerHandle);
	}
}

void ARangedWeaponBase::ApplyRecoil()
{
	if (!OwnerCharacter.IsValid())
		return;

	float VerticalRecoil = FMath::RandRange(RecoilConfig.RecoilVerticalMin, RecoilConfig.RecoilVerticalMax);
	float HorizontalRecoil = FMath::RandRange(RecoilConfig.RecoilHorizontalMin, RecoilConfig.RecoilHorizontalMax);

	RecoilConfig.CurrentRecoilVertical += VerticalRecoil;

	OwnerController->AddPitchInput(-VerticalRecoil);
	OwnerController->AddYawInput(HorizontalRecoil);

	// LastControlPitch = PC->GetControlRotation().Pitch;
	// PC->ClientStopCameraShake(RecoilShake);

}

void ARangedWeaponBase::RecoilRecovery(float DeltaTime)
{
	if (!OwnerCharacter.IsValid())
		return;    

	float VertRecovery = FMath::Min(
		RecoilConfig.CurrentRecoilVertical,
		RecoilConfig.CurrentRecoilVertical * DeltaTime * RecoilConfig.RecoilRecoverySpeed
	);

	OwnerController->AddPitchInput(VertRecovery);
	RecoilConfig.CurrentRecoilVertical -= VertRecovery;

	//// 5. 다음 프레임을 위해 현재 Pitch 저장 (자동 회복 적용 후)
	//LastControlPitch = OwnerController->GetControlRotation().Pitch;
}

void ARangedWeaponBase::ApplyDamage(const FHitResult& Hit, const FVector& ShotDir)
{
	if (!Hit.GetActor()) return;

	UGameplayStatics::ApplyPointDamage(
		Hit.GetActor(),
		Damage,
		ShotDir,
		Hit,
		OwnerController.Get(),
		this,
		UDamageType::StaticClass()

	);
}
