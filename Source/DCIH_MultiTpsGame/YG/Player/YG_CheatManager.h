// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "YG_CheatManager.generated.h"

/**
 * 
 */
UCLASS()
class DCIH_MULTITPSGAME_API UYG_CheatManager : public UCheatManager
{
	GENERATED_BODY()

public:
	// 발사 궤적 표시
	UFUNCTION(Exec)
	void BulletTrace(int32 bEnable = 1);

	// // 데미지 수치 표시
	// UFUNCTION(Exec)
	// void ShowDamage(int32 bEnable = 1);

	// // 무한 탄약
	// UFUNCTION(Exec)
	// void InfiniteAmmo();

	// // 총기 스탯 출력
	// UFUNCTION(Exec)
	// void WeaponStats();
};
