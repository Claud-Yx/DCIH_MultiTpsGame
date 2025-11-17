#include "JH/Weapon/RangedWeaponBase.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include <JH/Controller/JHPlayerController.h>


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


	//// �ʱ� Pitch �� ����
	//if (OwnerCharacter.IsValid())
	//{
	//	LastControlPitch 
	//		= OwnerController->GetControlRotation().Pitch;
	//}
}

void ARangedWeaponBase::Tick(float DeltaTime)
{
	//if (!bOwnerValid) {
	//	if (OwnerCharacter.IsValid()) {
	//		MouseControllPitch = OwnerController->GetControlRotation().Pitch;
	//	}
	//	bOwnerValid = true;
	//}
	RecoilRecovery(DeltaTime);

	if (RecoilConfig.CurrentRecoilVertical >= RecoilConfig.RecoilHorizontalMin) {
		// RecoilRecovery(DeltaTime);	
	}

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
	float currentTime = GetWorld()->GetTimeSeconds();

	if (currentTime - LastFireTime < FireRate)
	{
		return false;
	}

	LastFireTime = currentTime; // ������ �߻� �ð� ������Ʈ
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
	WeaponState = EWeaponState::Firing;
	bLastFireSuccess = false;

	if (!CanFire()) return;

	if (CurAmmo <= 0)
	{
		Reload();
		return;
	}

	//float currentTime = GetWorld()->GetTimeSeconds();

	//if (currentTime - LastFireTime < FireRate)
	//{
	//	return;
	//}

	//LastFireTime = currentTime; // ������ �߻� �ð� ������Ʈ
	ApplyRecoil();
	CurAmmo = FMath::Max(CurAmmo - 1, 0);

	bLastFireSuccess = true;
	WeaponState = EWeaponState::Equipping;

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

}

void ARangedWeaponBase::RecoilRecovery(float DeltaTime)
{
	if (!OwnerCharacter.IsValid())
		return;

	AJHPlayerController* PC = Cast<AJHPlayerController>(OwnerController.Get());

	float PlayerDownInput = PC->MousePitch;
	UE_LOG(LogTemp, Warning, TEXT("RecoilRecovery PlayerDownInput = %f"), PlayerDownInput);

	float RecoilLeft = RecoilConfig.CurrentRecoilVertical + PlayerDownInput;
	UE_LOG(LogTemp, Warning, TEXT("RecoilLeft = %f"), RecoilLeft);

	if (RecoilLeft <= 0.1f) {
		RecoilConfig.CurrentRecoilVertical = 0.f;
		PC->MousePitch = 0.f;
		return;
	}

	float RecoverAmount = RecoilLeft * DeltaTime * RecoilConfig.RecoilRecoverySpeed;

	RecoverAmount = FMath::Min(RecoverAmount, RecoilLeft);

	OwnerController->AddPitchInput(RecoverAmount);


	RecoilConfig.CurrentRecoilVertical -= RecoverAmount;


	//float VertRecovery = FMath::Min(
	//	RecoilConfig.CurrentRecoilVertical,
	//	(RecoilConfig.CurrentRecoilVertical) * DeltaTime * RecoilConfig.RecoilRecoverySpeed
	//);

	//OwnerController->AddPitchInput(VertRecovery);

	//RecoilConfig.CurrentRecoilVertical -= VertRecovery;
}

void ARangedWeaponBase::ApplyDamage(const FHitResult& Hit,const FVector& ShotDir)
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

void ARangedWeaponBase::DrawDebugTrace(const FVector& ShotDir, const FHitResult& Hit, const bool bHit) const
{

	DrawDebugLine(GetWorld(), GetMuzzleLocation(), GetAimPoint(), FColor::Green, false, 2.f, 0, 1.5f);

	if (bHit && Hit.bBlockingHit)
	{
		DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 8.f, FColor::Red, false, 2.f);
	}
	else
	{
		DrawDebugPoint(GetWorld(), GetAimPoint(), 6.f, FColor::Blue, false, 2.f);
	}
}