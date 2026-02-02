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

	
	







protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PickUpWeapon(class AWeaponBase* NewWeapon);

	void DropCurrentWeapon();

	void SwapWeapon();

private:
	UPROPERTY(VisibleAnywhere)
	TArray<FWeaponSlot> WeaponSlots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AWeaponBase> CurrentWeapon;

	void AttachToSocket(AWeaponBase* Weapon,const FName& SocketName);

};
