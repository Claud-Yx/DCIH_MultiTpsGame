// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YG/Weapon/YG_Weapon.h"
#include "YG_RangeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class DCIH_MULTITPSGAME_API AYG_RangeWeapon : public AYG_Weapon
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AttachMagazine( class AYG_Magazine* NewMagazine );

	UFUNCTION(BlueprintCallable)
	void RemoveMagazine();

	UFUNCTION(BlueprintCallable)
	void Fire();
	
	UFUNCTION(BlueprintCallable)
	bool CanFire();
	
	UFUNCTION(BlueprintCallable)
	class AYG_Magazine* GetMagazine();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="YG")
	float MaxRange;
	
	TWeakObjectPtr<class AYG_Magazine> CurMagazine;
	TArray<class UYGC_Muzzle*> Muzzles;
};
