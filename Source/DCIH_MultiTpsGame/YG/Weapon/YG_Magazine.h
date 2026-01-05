// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YG_Magazine.generated.h"

/**
 * 
 */
UCLASS()
class DCIH_MULTITPSGAME_API AYG_Magazine : public AActor
{
	GENERATED_BODY()

public:
	AYG_Magazine();
	
	/**
	 * 소비 시킬 탄환을 입력하여 실제 소비된 탄환을 반환
	 ** Param
	 * int32 NumObBullet: 소비 시킬 탄환 수
	 ** Return -> int32
	 * 실제로 소비된 탄환 수를 반환
	 */
	UFUNCTION( BlueprintCallable, Category="YG" )
	int32 SpendAmmo( int32 NumOfBullet );

	/**
	 * 장전 시킬 탄환을 입력하여 실제 장전된 탄환을 반환
	 * Param
	 * int32 NumObBullet: 장전 시킬 탄환 수
	 * Return -> int32
	 * 실제로 장전된 탄환 수를 반환
	 */
	UFUNCTION( BlueprintCallable, Category="YG" )
	int32 Reload( int32 NumOfBullet );

	UFUNCTION( BlueprintCallable, Category="YG" )
	FORCEINLINE bool IsFull() { return GetMaxAmmo() == GetCurAmmo(); }

	UFUNCTION( BlueprintCallable, Category="YG" )
	FORCEINLINE bool IsEmpty() { return GetCurAmmo() == 0; }

	UFUNCTION( BlueprintCallable, Category="YG" )
	class UYGDAB_Bullet* GetBulletType();

	UFUNCTION( BlueprintCallable, Category="YG" )
	FORCEINLINE int32 GetMaxAmmo() { return MaxAmmo; }

	UFUNCTION( BlueprintCallable, Category="YG" )
	FORCEINLINE int32 GetCurAmmo() { return CurAmmo; }

	UFUNCTION( BlueprintCallable, Category="YG" )
	FORCEINLINE int32 GetPallet() { return Pallet; }

	UFUNCTION( BlueprintCallable, Category="YG" )
	void SetBulletType( class UYGDAB_Bullet* NewBulletType );

	UFUNCTION( BlueprintCallable, Category="YG" )
	void SetMaxAmmo( int32 NewMaxAmmo );

	UFUNCTION( BlueprintCallable, Category="YG" )
	void SetCurAmmo( int32 NewCurAmmo );

	UFUNCTION( BlueprintCallable, Category="YG" )
	void SetPallet( int32 NewPallet );

protected:	
	///////////
	// Props //
	///////////

	/**
	 * 탄환 종류
	 */
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category="YG", meta=(AllowPrivateAccess=true) )
	class UYGDAB_Bullet* BulletType;

	/**
	 * 장전 가능한 최대 탄환 수
	 */
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category="YG", meta=(AllowPrivateAccess=true) )
	int32 MaxAmmo{ 1 };

	/**
	 * 남은 탄환 수
	 */
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category="YG", meta=(AllowPrivateAccess=true) )
	int32 CurAmmo{ 0 };

	/**
	 * 탄환 한 개에 들어있는 펠릿 수
	 * 샷 건 등에 사용
	 */
	UPROPERTY( BlueprintReadWrite, EditAnywhere, Category="YG", meta=(AllowPrivateAccess=true) )
	int32 Pallet{ 1 };
};
