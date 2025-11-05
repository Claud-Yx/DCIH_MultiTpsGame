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
	// PrimaryActorTick.bCanEverTick = true; 
	// SetActorTickEnabled(true);

	MuzzleSocketName = "Muzzle";
	TraceChannel = ECC_Visibility;
}

void ARangedWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

// void ARangedWeaponBase::Tick(float DeltaTime)
// {
// 	// Super::Tick(DeltaTime);
// 
// 	RecoilRecovery(DeltaTime);
// }

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
	float VerticalRecoil = FMath::RandRange(RecoilVerticalMin, RecoilVerticalMax);
	float HorizontalRecoil = FMath::RandRange(RecoilHorizontalMin, RecoilHorizontalMax);

	// 목표 반동값 누적
	RecoilValue.Y += VerticalRecoil;
	RecoilValue.X += HorizontalRecoil;


	if (APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetInstigatorController()))
	{
		PastRotation = PC->GetControlRotation();

		PC->AddPitchInput(-VerticalRecoil);
		PC->AddYawInput(HorizontalRecoil);
	}



	//if (APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetController()))
	//{
	//	//if (RecoilShake)
	//	//{
	//	//	// PC->ClientStartCameraShake(RecoilShake);
	//	//}
	//	//else
	//	{
	//		// 간단한 반동 입력
	//		PC->AddPitchInput(FMath::FRandRange(-1.5f, -3.0f));
	//		PC->AddYawInput(FMath::FRandRange(-0.5f, 0.5f));
	//	}
	//}
}

void ARangedWeaponBase::RecoilRecovery(float DeltaTime)
{
	//RecoilValue = FMath::Vector2DInterpTo(
	//	RecoilValue,
	//	FVector2D::ZeroVector,
	//	DeltaTime,
	//	RecoilRecoverySpeed
	//);

	//if (!OwnerCharacter.IsValid()) return;

	//APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetInstigatorController());
	//if (PC && !CurrentRecoil.IsNearlyZero(0.01f))
	//{
	//	// 반동 반대 방향으로 복구
	//	PC->AddPitchInput(CurrentRecoil.Y * DeltaTime * RecoilRecoverySpeed * 0.1f);
	//	PC->AddYawInput(-CurrentRecoil.X * DeltaTime * RecoilRecoverySpeed * 0.1f);
	//}

	APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetInstigatorController());
	if (!PC) return;

	// 현재 회전값 가져오기
	FRotator CurrentRot = PC->GetControlRotation();

	// 부드럽게 회전 복귀
	FRotator NewRot = FMath::RInterpTo(CurrentRot, PastRotation, DeltaTime, RecoilRecoverySpeed);

	PC->SetControlRotation(NewRot);
}


//// 인자 없이 그냥
//FVector ARangedWeaponBase::GetShotDirection() const
//{
//	return (GetAimPoint() - GetMuzzleLocation()).GetSafeNormal();
//}