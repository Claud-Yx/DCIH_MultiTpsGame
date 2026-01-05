// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YGF_Weapon.generated.h"

/**
 * 탄환을 발사하기 위한 정보
 * 피격 지점의 이펙트 정보 또한 담을 예정
 */
USTRUCT( BlueprintType )
struct DCIH_MULTITPSGAME_API FYG_MuzzleFireData
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category="YG" )
	class UYGDAB_Bullet* Bullet;

	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category="YG" )
	float MaxRange{ 10000.f };

	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category="YG" )
	TEnumAsByte<ECollisionChannel> CollisionChannel;
};
