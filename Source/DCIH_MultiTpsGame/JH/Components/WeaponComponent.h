// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JH/Weapon/WeaponPickUpInterface.h"
#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DCIH_MULTITPSGAME_API UWeaponComponent : public UActorComponent, public IWeaponPickUpInterface
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void PickUpWeapon_Implementation(class UWeaponDataAsset* WeaponDataAsset);


	UPROPERTY()
	class AWeaponBase* CurrentWeapon;

};
