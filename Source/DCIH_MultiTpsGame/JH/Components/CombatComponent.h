#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JH/Interface/InteractTarget.h"
#include "CombatComponent.generated.h"

class AWeaponBase;



USTRUCT(BlueprintType)
struct FWeaponContainer 
{
	GENERATED_BODY()

	UPROPERTY()
	int32 MaxCount = 0;

	UPROPERTY()
	TArray<TObjectPtr<AWeaponBase>> Weapons;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DCIH_MULTITPSGAME_API UCombatComponent : public UActorComponent, public IInteractTarget
{
	GENERATED_BODY()

public:	
	UCombatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void EquipWeapon(AWeaponBase* Weapon, FName SocketName);

	UFUNCTION()
	void SwapWeapon();

	UFUNCTION()
	void DropCurrentWeapon();


	void PickUpWeapon(AWeaponBase* NewWeapon);


	UPROPERTY()
	TMap<EWeaponCategory, FWeaponContainer> WeaponContainers;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AWeaponBase> CurrentWeapon;


protected:
	virtual void OnInteract_Implementation(AActor* Interactor) override;
};
