#pragma once

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
    UnEquipped,
    Holstered,
    Equipped,
    
    Firing,
    Reloading
};