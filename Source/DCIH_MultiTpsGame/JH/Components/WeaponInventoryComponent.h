//#pragma once
//
//#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
//#include "WeaponInventoryComponent.generated.h"
//
//class EWeaponCategory;
//class AWeaponBase;
//
//USTRUCT(BlueprintType)
//struct FWeaponSLot
//{
//	GENERATED_BODY()
//	
//	UPROPERTY()
//	int32 MaxCount;
//	UPROPERTY()
//	TArray<TObjectPtr<AWeaponBase>> Weapons;
//};
//
//UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
//class DCIH_MULTITPSGAME_API UWeaponInventoryComponent : public UActorComponent
//{
//	GENERATED_BODY()
//
//public:	
//	UWeaponInventoryComponent();
//protected:
//	virtual void BeginPlay() override;
//public:	
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
//
//	UFUNCTION()
//	void AddWeapon(AWeaponBase NewWeapon);
//
//	UFUNCTION()
//	void EquipWeapon();
//	
//	UFUNCTION()
//	void DropCurrentWeapon();
//
//	UFUNCTION()
//	void SwapWeapon();
//
//private:
//	UPROPERTY()
//	TMap<EWeaponCategory, FWeaponSLot> WeaponSlots;
//
//	UPROPERTY()
//	TObjectPtr<AWeaponBase> CurrentWeapon;
//};