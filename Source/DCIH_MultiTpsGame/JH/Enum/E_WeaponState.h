#pragma once

UENUM(BlueprintType)
enum class EWeaponState2 : uint8
{
    //Idle    UMETA(DisplayName = "Idle"),
    //Firing  UMETA(DisplayName = "Idle"),
    //Reloading   UMETA(DisplayName = "Idle")

    UnEquipping,
    Holstering,
    Equipping,
    
    Firing,
    Reloading,
};