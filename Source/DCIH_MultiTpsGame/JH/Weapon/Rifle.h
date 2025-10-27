#pragma once

#include "CoreMinimal.h"
#include "JH/Weapon/RangedWeaponBase.h"
#include "Rifle.generated.h"

UCLASS()
class DCIH_MULTITPSGAME_API ARifle : public ARangedWeaponBase
{
	GENERATED_BODY()

public:
	ARifle();

	virtual void Fire() override;
protected:
	//void ApplyHitDamage(const FHitResult& Hit, const FVector& ShotDir);
};
