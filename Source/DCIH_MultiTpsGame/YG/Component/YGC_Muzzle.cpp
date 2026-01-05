// Fill out your copyright notice in the Description page of Project Settings.


#include "YG/Component/YGC_Muzzle.h"

#include "YG/DataAsset/YGDAB_Bullet.h"

extern TAutoConsoleVariable<int32> CVarBulletTrace;

void UYGC_Muzzle::Fire( const FYG_MuzzleFireData& FireData )
{
	if ( GWorld )
	{
		FHitResult Hit;
		FVector    StartLocation = GetComponentLocation();
		FVector    EndLocation   = GetComponentLocation() + GetForwardVector() * FireData.MaxRange;

		// 관통형 공격이라면 여기서 분기를 일으키고 Multi 부분도 구현한다.
		GWorld->LineTraceSingleByChannel( Hit, StartLocation, EndLocation, FireData.CollisionChannel );

		if ( CVarBulletTrace.GetValueOnGameThread() > 0 )
		{
			DrawDebugLine( GWorld, StartLocation, Hit.bBlockingHit ? Hit.ImpactPoint : EndLocation, FColor::Red, false, 1.f, 0, 1 );
			if ( Hit.bBlockingHit )
			{
				DrawDebugPoint( GWorld, Hit.ImpactPoint, 5.f, FColor::Orange, false, 1.f );
			}
		}
	}
}
