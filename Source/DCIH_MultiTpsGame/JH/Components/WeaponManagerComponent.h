#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JH/Enum/E_WeaponTypes.h"
#include "JH/Weapon/WeaponDataAsset.h"

#include "JH/Weapon/WeaponBase.h"
#include "WeaponManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponChanged);

class AWeaponBase;


//USTRUCT(BlueprintType)
//struct FWeaponSlot
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
//	EWeaponCategory Category;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
//	TObjectPtr<AWeaponBase> Weapon = nullptr;
//
//	bool IsEmpty() const { return Weapon == nullptr; }
//};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DCIH_MULTITPSGAME_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponManagerComponent();
protected:
	virtual void BeginPlay() override;

public:

	void PickUp(class AWeaponBase* NewWeapon);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Swap(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void DropCurrent();

public:
	UFUNCTION(BlueprintPure, Category = "Weapon")
	FORCEINLINE AWeaponBase* GetCurrentWeapon() const 
	{ return CurrentWeapon.Get(); }

	UFUNCTION(BLueprintPure)
	EWeaponCategory GetCurrentWeaponCategory() const;

	//UFUNCTION(BlueprintPure, Category = "Weapon")
	//bool HasWEeaponInSlot(int32 SlotIndex) const;


public:
	//UPROPERTY(BlueprintAssignable, Category = "Events")
	//FOnWeaponChanged OnCurrentWeaponChanged;

	//UPROPERTY(BlueprintAssignable, Category = "Events")
	//FOnPickUpFailed OnPickUpFailed;


	

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnWeaponChanged OnWeaponChanged; 



private:

	int32 GetEmptySlotIndex(EWeaponCategory Cat) const;

	void HolsterAll();

	void AttachToSocket(AWeaponBase* Weapon, const FName& SocketName);

private:
	static constexpr int32 SLOT_RANGED_1 = 0;
	static constexpr int32 SLOT_RANGED_2 = 1;
	static constexpr int32 SLOT_MELEE = 2;
	static constexpr int32 SLOT_COUNT = 3;

	UPROPERTY(EditAnywhere, Category = "Slots")
	TArray<TObjectPtr<AWeaponBase>>Slots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<AWeaponBase> CurrentWeapon;
};