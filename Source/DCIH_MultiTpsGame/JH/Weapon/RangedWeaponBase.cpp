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
}

void ARangedWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

bool ARangedWeaponBase::CanFire() const
{
	//const bool bPawnValid = OwningPawn.IsValid();
	return 
		!(GetWeaponState() == EWeaponState::Reloading) && 
		curAmmo > 0;
}

void ARangedWeaponBase::Fire()
{
	if(!CanFire())
	{
		Reload();
		return;
	}
}

void ARangedWeaponBase::Reload()
{
	if (GetWeaponState() == EWeaponState::Reloading)
		return;
	

	SetWeaponState(EWeaponState::Reloading);

	//if (UWorld* World = GetWorld())
	//{
	//	World->GetTimerManager().SetTimer(
	//		ReloadTimerHandle,
	//		this,
	//		&ARangedWeaponBase::FinishReload,
	//		ReloadTime,
	//		false
	//	);
	//}
	//else
	//{
	//	FinishReload();
	//}

	FinishReload();
}

void ARangedWeaponBase::FinishReload()
{
	curAmmo = maxAmmo;
	SetWeaponState(EWeaponState::Idle);

	//if (UWorld* World = GetWorld())
	//{
	//	World->GetTimerManager().ClearTimer(ReloadTimerHandle);
	//}
}

FVector ARangedWeaponBase::GetMuzzleLocation() const
{
	if (mesh && mesh->DoesSocketExist(muzzleSocketName))
	{
		return mesh->GetSocketLocation(muzzleSocketName);
	}

	UE_LOG(LogTemp, Warning, TEXT("No valid muzzle socket (%s). Using ActorLocation Instead."),
		*GetName(), *muzzleSocketName.ToString());

	return GetActorLocation();
}

FVector ARangedWeaponBase::GetAimPoint() const
{
	FVector camStartLoc;
	FRotator camRot;

	if (APawn* P = owningPawn.Get())
	{
		if (AController* C = P->GetController())
		{
			C->GetPlayerViewPoint(camStartLoc, camRot);
		}
	}
	const FVector camEndLoc = camStartLoc + camRot.Vector() * traceRange;


	
	FHitResult camHit;
	FCollisionQueryParams camParams(SCENE_QUERY_STAT(CameraAimTrace), false, this);
	if (APawn* P = owningPawn.Get()) 
	{
		camParams.AddIgnoredActor(P);
	}
	if (mesh) 
	{
		camParams.AddIgnoredComponent(Cast<UPrimitiveComponent>(mesh));
	}

	if (GetWorld()->LineTraceSingleByChannel
	(
		camHit,
		camStartLoc,
		camEndLoc,
		traceChannel,
		camParams) && camHit.bBlockingHit)
	{
		return camHit.ImpactPoint;
	}
	return camEndLoc;
}

//// 인자 없이 그냥
//FVector ARangedWeaponBase::GetShotDirection() const
//{
//	return (GetAimPoint() - GetMuzzleLocation()).GetSafeNormal();
//}

