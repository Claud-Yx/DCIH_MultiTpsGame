#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponManagerComponent.generated.h"


class AWeaponBase;


USTRUCT(BlueprintType)
struct FWeaponSlot
{
	GENERATED_BODY()

	UPROPERTY()
	int32 MaxCount;

	UPROPERTY()
	TArray<TObjectPtr<AWeaponBase>> Weapons;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DCIH_MULTITPSGAME_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponManagerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void PickUpWeapon(class AWeaponBase* NewWeapon);

	void DropCurrentWeapon();

	void SwapWeapon(int32 SlotNum);

	
protected:
	virtual void BeginPlay() override;

private:
	void AttachToSocket(AWeaponBase* Weapon,const FName& SocketName);
	UPROPERTY(VisibleAnywhere)

	TArray<FWeaponSlot> WeaponSlots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AWeaponBase> CurrentWeapon;



	static constexpr int32 MAX_WEAPON_SLOT{ 2 };
	static constexpr int32 RANGED_WEAPON{ 0 };
	static constexpr int32 MELEE_WEAPON{ 1 };
};
