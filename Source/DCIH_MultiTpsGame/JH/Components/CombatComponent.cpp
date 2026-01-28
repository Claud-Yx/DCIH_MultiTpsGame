#include "JH/Components/CombatComponent.h"
#include "GameFramework/Character.h"
#include "JH/Weapon/WeaponBase.h"
#include "JH/Weapon/WeaponDataAsset.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCombatComponent::EquipWeapon(AWeaponBase* Weapon)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter) return;

	USkeletalMeshComponent* Mesh = OwnerCharacter->GetMesh();

	if (CurrentWeapon && CurrentWeapon != Weapon)
	{
		Weapon->AttachToComponent
		(
			Mesh,
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			CurrentWeapon->GetWeaponData()->HolsterSocket
		);
	}
	else {
		Weapon->AttachToComponent
		(
			Mesh,
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			Weapon->GetWeaponData()->HandSocket
			// FName("WeaponSocket")
		);

		CurrentWeapon = Weapon;
	}
	
	// CurrentWeapon = Weapon;

}

void UCombatComponent::SwapWeapon()
{
	if (FirstWeapon && SecondWeapon)
	{
		CurrentWeapon == FirstWeapon ? 
			CurrentWeapon = SecondWeapon : CurrentWeapon = FirstWeapon;
	}

}

void UCombatComponent::DropCurrentWeapon()
{
	CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void UCombatComponent::PickUpWeapon(AWeaponBase* NewWeapon)
{
	if (NewWeapon == FirstWeapon || NewWeapon == SecondWeapon) return;

	if (!FirstWeapon)
	{
		FirstWeapon = NewWeapon;
		EquipWeapon(FirstWeapon);
	}
	else if (!SecondWeapon)
	{
		SecondWeapon = NewWeapon;
		EquipWeapon(SecondWeapon);
	}
	else
	{
		DropCurrentWeapon();
		PickUpWeapon(NewWeapon);
	}
}

void UCombatComponent::OnInteract_Implementation(AActor* Interactor)
{
	AWeaponBase* NewWeapon = Cast<AWeaponBase>(Interactor);
	if (NewWeapon) 
	{
		PickUpWeapon(NewWeapon);
	}
}
