// Fill out your copyright notice in the Description page of Project Settings.


#include "JH/Weapon/Shotgun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"

AShotgun::AShotgun()
{
	TraceRange = 1500.f;

	CurAmmo = 8;
	MaxAmmo = 8;
	Damage = 15.f;

	PelletNum = 10;
}

void AShotgun::Fire()
{
	Super::Fire();

	if (bShowLineTrace) 
	{

	}

	for (int32 i = 0; i < PelletNum; ++i)
	{
		//ApplyDamage();
	}

	HitScan();
}

void AShotgun::HitScan()
{
	FVector StartLocaion;
	FRotator MuzzleRotation;
	OwnerController->GetPlayerViewPoint(StartLocaion, MuzzleRotation);



	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(ShotgunTrace), true, this);

	if (OwnerCharacter.IsValid())
	{
		TraceParams.AddIgnoredActor(OwnerCharacter.Get());
	}

	if(MeshComp)
	{ 
		TraceParams.AddIgnoredComponent(MeshComp.Get());
	}

	FVector ShotDir = MuzzleRotation.Vector();

	for (int32 i = 0; i < PelletNum; ++i)
	{
		FVector RandomDir = FMath::VRandCone(ShotDir, FMath::DegreesToRadians(SpreadAngle));
		FVector EndLocation = (GetAimPoint() - GetMuzzleLocation()) * RandomDir * TraceRange;
		// DrawDebugTrace(EndLocation, Hit, bHit);
	}


	FHitResult Hit;
	// const bool bHit = GetWorld()->LineTraceSingleByChannel()
}	