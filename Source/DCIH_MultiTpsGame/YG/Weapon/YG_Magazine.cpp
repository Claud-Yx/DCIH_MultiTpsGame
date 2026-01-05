// Fill out your copyright notice in the Description page of Project Settings.


#include "YG/Weapon/YG_Magazine.h"

AYG_Magazine::AYG_Magazine()
{
}

int32 AYG_Magazine::SpendAmmo( int32 NumOfBullet )
{
	int32 SpentAmmo = NumOfBullet;
	int32 Remains   = GetCurAmmo() - SpentAmmo;
	SetCurAmmo( Remains );
	if ( Remains < 0 )
	{
		SpentAmmo += Remains;
	}

	return SpentAmmo;
}

int32 AYG_Magazine::Reload( int32 NumOfBullet )
{
	int32 ReloadedAmmo = NumOfBullet;
	int32 Remains      = GetCurAmmo() + ReloadedAmmo;
	SetCurAmmo( Remains );
	if ( Remains > GetMaxAmmo() )
	{
		ReloadedAmmo -= (Remains - GetMaxAmmo());
	}

	return ReloadedAmmo;
}

void AYG_Magazine::SetBulletType( class UYGDAB_Bullet* NewBulletType )
{
	BulletType = NewBulletType;
}

void AYG_Magazine::SetMaxAmmo( int32 NewMaxAmmo )
{
	MaxAmmo = FMath::Max( 1, NewMaxAmmo );
}

void AYG_Magazine::SetCurAmmo( int32 NewCurAmmo )
{
	CurAmmo = FMath::Clamp( NewCurAmmo, 0, GetMaxAmmo() );
}

void AYG_Magazine::SetPallet( int32 NewPallet )
{
	Pallet = FMath::Max( 1, NewPallet );
}

class UYGDAB_Bullet* AYG_Magazine::GetBulletType()
{
	return BulletType;
}
