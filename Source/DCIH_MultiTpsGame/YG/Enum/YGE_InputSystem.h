// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EYG_InputMappingContext : uint8
{
	None,
	PlayerCharacter_DefaultMovement,
	PlayerCharacter_HoldingGun,
};

UENUM(BlueprintType)
enum class EYG_InputAction : uint8
{
	None,
	AimGun,
	Crouching,
	FireGun,
	Interaction,
	Jump,
	TpsMove
};
