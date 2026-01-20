// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JH/Weapon/RangedWeaponBase.h"
#include "Shotgun.generated.h"

/**
 *
 */
UCLASS()
class DCIH_MULTITPSGAME_API AShotgun : public ARangedWeaponBase
{
	GENERATED_BODY()

public:
	AShotgun();

	virtual void Fire() override;


};
