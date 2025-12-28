// Fill out your copyright notice in the Description page of Project Settings.


#include "YG/Player/YG_CheatManager.h"

TAutoConsoleVariable<int32> CVarBulletTrace( TEXT( "r.BulletTrace" ), 0, TEXT( "Show bullet trajectory" ) );

void UYG_CheatManager::BulletTrace( int32 bEnable )
{
	CVarBulletTrace->Set( bEnable );
	UE_LOG( LogTemp, Warning, TEXT("BulletTrace: %s"),
	        bEnable ? TEXT("ON") : TEXT("OFF")
	);
}
