// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
    Idle        UMETA(DisplayName = "Idle"),
    Walking     UMETA(DisplayName = "Walking"),
	Running     UMETA(DisplayName = "Running"),
    Jumping     UMETA(DisplayName = "Jumping"),
	Rolling	    UMETA(DisplayName = "Rolling"),
	Crouching	UMETA(DisplayName = "Crouching"),
	Proning     UMETA(DisplayName = "Proning"),
    Dead        UMETA(DisplayName = "Dead")
};

UENUM(BlueprintType)
enum class ECharacterWeaponState : uint8
{
    Shooting    UMETA(DisplayName = "Shooting"),
    Reloading   UMETA(DisplayName = "Reloading")
};
