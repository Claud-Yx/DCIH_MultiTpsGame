//#include "JH/Components/CombatComponent.h"
//#include "GameFramework/Character.h"
//#include "JH/Weapon/WeaponBase.h"
//#include "JH/Weapon/WeaponDataAsset.h"
//
//UCombatComponent::UCombatComponent()
//{
//	PrimaryComponentTick.bCanEverTick = true;
//
//}
//
//void UCombatComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//	WeaponContainers.Add(
//		EWeaponCategory::Ranged,
//		FWeaponContainer{ 2 }
//	);
//	WeaponContainers.Add(
//		EWeaponCategory::Melee,
//		FWeaponContainer{ 1 }
//	);
//
//}
//
//
//void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//}
//
//void UCombatComponent::EquipWeapon(AWeaponBase* Weapon, FName SocketName)
//{
//	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
//	if (!OwnerCharacter) return;
//
//	USkeletalMeshComponent* Mesh = OwnerCharacter->GetMesh();
//
//	//if (CurrentWeapon && CurrentWeapon != Weapon)
//	{
//		Weapon->AttachToComponent
//		(
//			Mesh,
//			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
//			Weapon->GetWeaponData()->HolsterSocket
//		);
//
//		Weapon->OnEquipped(Cast<ACharacter>(GetOwner()));
//	}
//	//else {
//	//	Weapon->AttachToComponent
//	//	(
//	//		Mesh,
//	//		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
//	//		Weapon->GetWeaponData()->HandSocket
//	//		// FName("WeaponSocket")
//	//	);
//
//	CurrentWeapon = Weapon;
//	// }
//
//	// CurrentWeapon = Weapon;
//
//}
//
//void UCombatComponent::SwapWeapon()
//{
//	if (FirstWeapon && SecondWeapon)
//	{
//		CurrentWeapon == FirstWeapon ?
//			CurrentWeapon = SecondWeapon : CurrentWeapon = FirstWeapon;
//	}
//
//}
//
//void UCombatComponent::DropCurrentWeapon()
//{
//	CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
//}
//
//void UCombatComponent::PickUpWeapon(AWeaponBase* NewWeapon)
//{
//	// if (NewWeapon == FirstWeapon || NewWeapon == SecondWeapon) return;
//
//	EWeaponCategory Category = NewWeapon->GetWeaponData()->Category;
//
//	FWeaponContainer& Container = WeaponContainers[Category];
//
//	if (Container.Weapons.Num() >= Container.MaxCount)
//	{
//		if (CurrentWeapon && CurrentWeapon->GetWeaponData()->Category == Category)
//		{
//			Container.Weapons.Remove(CurrentWeapon);
//		}
//		else 
//		{
//			return;
//		}
//	}
//
//	Container.Weapons.Add(NewWeapon);
//
//	if (!CurrentWeapon)
//	{
//		CurrentWeapon = NewWeapon;
//		EquipWeapon(NewWeapon, NewWeapon->GetWeaponData()->HandSocket);
//	}
//	else
//	{
//		EquipWeapon(NewWeapon, NewWeapon->GetWeaponData()->HolsterSocket);
//	}
//}
//
//void UCombatComponent::OnInteract_Implementation(AActor* Interactor)
//{
//	AWeaponBase* NewWeapon = Cast<AWeaponBase>(Interactor);
//	if (NewWeapon)
//	{
//		PickUpWeapon(NewWeapon);
//	}
//}
