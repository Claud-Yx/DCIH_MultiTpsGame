#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class AWeaponBase;

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
	void EquipWeapon(AWeaponBase* Weapon);

	UFUNCTION()
	void SwapWeapon();

	UFUNCTION()
	void DropCurrentWeapon();


	void PickUpWeapon(AWeaponBase* NewWeapon);

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AWeaponBase> CurrentWeapon;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AWeaponBase> FirstWeapon;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AWeaponBase> SecondWeapon;

	virtual void OnInteract_Implementation(AActor* Interactor) override;
};
