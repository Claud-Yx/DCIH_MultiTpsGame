#pragma once

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
    UnEquipping,
    Holstering,
    Equipping,
    
    Firing,
    Reloading,
};