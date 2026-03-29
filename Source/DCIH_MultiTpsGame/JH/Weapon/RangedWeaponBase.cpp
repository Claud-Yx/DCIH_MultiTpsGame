#include "JH/Weapon/RangedWeaponBase.h"

#include "JH/Weapon/WeaponDataAsset.h"
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

	MuzzleSocket = TEXT("Muzzle");
	// TraceChannel = ECC_Visibility;
	// MagazineNum = 0;
}

void ARangedWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponData)
	{
		CurAmmo = WeaponData->MaxAmmo;
		MaxAmmo = WeaponData->MaxAmmo;

		// LastFireTime을 FireRate 이전으로 초기화해서 즉시 발사 가능하게
		LastFireTime = -WeaponData->FireRate;
	}
}

void ARangedWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RecoilRecovery(DeltaTime);
}

void ARangedWeaponBase::Fire()
{
	bLastFireSuccess = false;

	if (!CanFire()) return;

	if (CurAmmo <= 0)
	{
		Reload();
		return;
	}

	ConsumeAmmo(1);
	ApplyRecoil();
	
	// Fire();

	bLastFireSuccess = true;


	//WeaponState = EWeaponState::Firing;
	//bLastFireSuccess = false;

	//if (!CanFire()) return;

	//if (CurAmmo <= 0)
	//{
	//	Reload();
	//	return;
	//}

	//ApplyRecoil();
	//
	//ConsumeAmmo(1);

	//bLastFireSuccess = true;
	//WeaponState = EWeaponState::Equipped;
}

//void ARangedWeaponBase::AddMagazine(int32 MagazineAmount)
//{
//	MagazineNum = FMath::Max(0, MagazineNum + MagazineAmount);
//
//	OnMagazineChanged.Broadcast(MagazineNum);
//}

FVector ARangedWeaponBase::GetMuzzleLocation() const
{
	if (MeshComp && MeshComp->DoesSocketExist(MuzzleSocket))
	{
		return MeshComp->GetSocketLocation(MuzzleSocket);
	}
	return GetActorLocation();
}

FVector ARangedWeaponBase::GetAimPoint() const
{
	FVector CamLoc;
	FRotator CamRot;

	OwnerController->GetPlayerViewPoint(CamLoc, CamRot);


	const float Range = WeaponData ? WeaponData->TraceRange : 20000.f;
	const FVector End = CamLoc + CamRot.Vector() * Range;

	FHitResult Hit;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(AimTrace), false);
	Params.AddIgnoredActor(this);
	if (OwnerCharacter.IsValid()) Params.AddIgnoredActor(OwnerCharacter.Get());

	if (GetWorld()->LineTraceSingleByChannel(Hit, CamLoc, End, ECC_Visibility, Params)
		&& Hit.bBlockingHit)
	{
		return Hit.ImpactPoint;
	}
	return End;
}

void ARangedWeaponBase::ApplyHitDamage(const FHitResult& Hit, const FVector& ShotDir)
{
	if (!Hit.GetActor() || !WeaponData) return;

	UGameplayStatics::ApplyPointDamage
	(
		Hit.GetActor(),
		WeaponData->Damage,
		ShotDir,
		Hit,
		OwnerController.Get(),
		this,
		UDamageType::StaticClass()
	);
}

void ARangedWeaponBase::DrawDebugTrace(const FVector& Start, const FVector& End, const FHitResult& Hit, bool bHit) const
{
#if ENABLE_DRAW_DEBUG
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.5f, 0, 1.f);

	if (bHit && Hit.bBlockingHit)
		DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 8.f, FColor::Red, false, 1.5f);
	else
		DrawDebugPoint(GetWorld(), End, 6.f, FColor::Blue, false, 1.5f);
#endif
}

bool ARangedWeaponBase::CanFire() const
{
	if (WeaponState != EWeaponState::Equipped )
	{
		return false;
	}
	if(WeaponData == nullptr)
	{
		return false;
	}

	float CurrentTime = GetWorld()->GetTimeSeconds();

	return (CurrentTime - LastFireTime) >= WeaponData->FireRate;


	//if (currentTime - LastFireTime < FireRate)
	//{
	//	return false;
	//}

	//LastFireTime = currentTime;

	//return true;

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
		WeaponData->ReloadTime,
		false
	);
}

void ARangedWeaponBase::FinishReload()
{
	CurAmmo = MaxAmmo;
	SetWeaponState(EWeaponState::Equipped);
	OnAmmoChanged.Broadcast(CurAmmo, MaxAmmo);
	GetWorld() ->GetTimerManager().ClearTimer(ReloadTimerHandle);
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

	CachedJHController = Cast<AJHPlayerController>(OwnerController.Get());

	float PlayerDownInput = CachedJHController->MousePitch;
	// UE_LOG(LogTemp, Warning, TEXT("PlayerDownInput: %f"), PlayerDownInput);

	float TotalRecovery = RecoilConfig.CurrentRecoilVertical + PlayerDownInput;
	// UE_LOG(LogTemp, Warning, TEXT("TotalRecovery: %f"), TotalRecovery);

	if (TotalRecovery < RecoilConfig.RecoilVerticalMin) {
		RecoilConfig.CurrentRecoilVertical = 0.f;
		CachedJHController->MousePitch = 0.f;
		return;
	}

	float RecoverAmount = TotalRecovery * DeltaTime * RecoilConfig.RecoilRecoverySpeed;

	RecoverAmount = FMath::Min(RecoverAmount, TotalRecovery);

	CachedJHController->AddPitchInput(RecoverAmount);


	RecoilConfig.CurrentRecoilVertical -= RecoverAmount;


	//float VertRecovery = FMath::Min(
	//	RecoilConfig.CurrentRecoilVertical,
	//	(RecoilConfig.CurrentRecoilVertical) * DeltaTime * RecoilConfig.RecoilRecoverySpeed
	//);

	//OwnerController->AddPitchInput(VertRecovery);

	//RecoilConfig.CurrentRecoilVertical -= VertRecovery;
}


void ARangedWeaponBase::ConsumeAmmo(int32 Amount)
{
	CurAmmo = FMath::Clamp(CurAmmo - Amount, 0, MaxAmmo);
	OnAmmoChanged.Broadcast(CurAmmo, MaxAmmo);

	// LastFireTime은 CanFire 통과 시점에 갱신
	LastFireTime = GetWorld()->GetTimeSeconds();
	// Broadcast(CurAmmo, MaxAmmo);
}
