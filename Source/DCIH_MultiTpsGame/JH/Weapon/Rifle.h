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
public:
	virtual void Tick(float DeltaTime) override;

	virtual void Fire() override;
private:
	UFUNCTION(BlueprintCallable,Category ="Fire")
	void HitScan();
	//UFUNCTION(BlueprintCallable, Category = "Fire")
	//void DrawDebugTrace(const FVector& ShotDir, const FHitResult& Hit, const bool bHit) const;
	//void ApplyHitDamage(const FHitResult& Hit, const FVector& ShotDir);
};
