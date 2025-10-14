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

	virtual void Use() override { Super::Use(); }
protected:
	//bool TraceBullet(const FVector& MuzzleLoc, const FVector& TraceEnd, FHitResult& OutHit) const;

	//void ApplyHitDamage(const FHitResult& Hit, const FVector& ShotDir);

	//void DrawFireDebug(const FVector& Start, const FVector& End, bool bHit, const FVector& HitLocation) const;
};
