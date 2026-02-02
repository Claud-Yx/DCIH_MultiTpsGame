#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EWeaponCategory : uint8
{
	Ranged UMETA(DisplayName = "Ranged"),
	Melee  UMETA(DisplayName = "Melee")
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Rifle         UMETA(DisplayName = "Rifle"),
	Shotgun       UMETA(DisplayName = "Shotgun"),
	Sniper        UMETA(DisplayName = "Sniper"),
	RocketLauncher UMETA(DisplayName = "RocketLauncher"),

	Bayonet       UMETA(DisplayName = "Bayonet"),
	DoubleSword   UMETA(DisplayName = "DoubleSword"),
	Dagger        UMETA(DisplayName = "Dagger")
};