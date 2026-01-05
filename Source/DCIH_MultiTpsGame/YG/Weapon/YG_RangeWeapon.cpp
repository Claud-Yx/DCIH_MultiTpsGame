// Fill out your copyright notice in the Description page of Project Settings.


#include "YG/Weapon/YG_RangeWeapon.h"

#include "YG_Magazine.h"
#include "YG/Component/YGC_Muzzle.h"


void AYG_RangeWeapon::AttachMagazine( class AYG_Magazine* NewMagazine )
{
	CurMagazine = NewMagazine;
}

void AYG_RangeWeapon::RemoveMagazine()
{
	CurMagazine = nullptr;
}

void AYG_RangeWeapon::Fire()
{
	if ( !CanFire() )
	{
		return;
	}

	for ( auto& Muzzle : Muzzles )
	{
		// 탄환을 소모하는게 불가능 하다면 못 쏨
		if ( CurMagazine->SpendAmmo( 1 ) < 1 )
		{
			break;
		}

		FYG_MuzzleFireData FireData;
		FireData.Bullet           = CurMagazine->GetBulletType();
		FireData.CollisionChannel = ECC_EngineTraceChannel1;
		FireData.MaxRange         = MaxRange;

		Muzzle->Fire( FireData );
	}
}

bool AYG_RangeWeapon::CanFire()
{
	auto Magazine = CurMagazine.Get();
	if ( !Magazine )
	{
		return false;
	}

	if ( Magazine->IsEmpty() )
	{
		return false;
	}

	return true;
}

class AYG_Magazine* AYG_RangeWeapon::GetMagazine()
{
	return CurMagazine.Get();
}

void AYG_RangeWeapon::BeginPlay()
{
	Super::BeginPlay();

	GetComponents<UYGC_Muzzle>( Muzzles );
}
