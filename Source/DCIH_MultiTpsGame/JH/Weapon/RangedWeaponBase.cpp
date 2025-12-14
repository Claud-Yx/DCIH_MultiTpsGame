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
	
	ConsumeAmmo(1);
	// CurAmmo = FMath::Max(CurAmmo - 1, 0);

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
	AmmoChangedDelegate.Broadcast(CurAmmo, MaxAmmo);

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
	
	// UE_LOG(LogTemp, Warning, TEXT("CurrentRecoilVertical : %f"), RecoilConfig.CurrentRecoilVertical);
}

void ARangedWeaponBase::RecoilRecovery(float DeltaTime)
{
	if (RecoilConfig.CurrentRecoilVertical <= 0.01f)
		return;

	if (!OwnerCharacter.IsValid())
		return;

	JHController = Cast<AJHPlayerController>(OwnerController.Get());

	float PlayerDownInput = JHController->MousePitch;
	// UE_LOG(LogTemp, Warning, TEXT("PlayerDownInput: %f"), PlayerDownInput);

	float TotalRecovery = RecoilConfig.CurrentRecoilVertical + PlayerDownInput;
	// UE_LOG(LogTemp, Warning, TEXT("TotalRecovery: %f"), TotalRecovery);

	if (TotalRecovery < RecoilConfig.RecoilVerticalMin) {
		RecoilConfig.CurrentRecoilVertical = 0.f;
		JHController->MousePitch = 0.f;
		return;
	}

	float RecoverAmount = TotalRecovery * DeltaTime * RecoilConfig.RecoilRecoverySpeed;

	RecoverAmount = FMath::Min(RecoverAmount, TotalRecovery);

	JHController->AddPitchInput(RecoverAmount);


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

void ARangedWeaponBase::ConsumeAmmo(int32 Amount)
{
	CurAmmo = FMath::Clamp(CurAmmo - Amount, 0, MaxAmmo);

	AmmoChangedDelegate.Broadcast(CurAmmo, MaxAmmo);
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