// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "YG/Struct/YGF_Weapon.h"
#include "YGC_Muzzle.generated.h"

/**
 * 탄환의 출구가 되는, 위치와 방향값을 가진 컴포넌트
 * 총구 섬광 또한 여기서 표현
 * 역할: 정보를 저장하지 않고 위치와 방향, 발사 동작까지
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DCIH_MULTITPSGAME_API UYGC_Muzzle : public UArrowComponent
{
	GENERATED_BODY()
	
public:
	// 총알정보를 받아 히트스캔 방식으로 대상에 데미지, 이펙트 등을 전달
	UFUNCTION(BlueprintCallable, Category = "YG")
	void Fire(const FYG_MuzzleFireData& FireData);

protected:
	
};
