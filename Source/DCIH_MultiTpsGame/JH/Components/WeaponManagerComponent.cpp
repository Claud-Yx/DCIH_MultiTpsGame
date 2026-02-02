#include "JH/Components/WeaponManagerComponent.h"
#include "JH/Weapon/WeaponBase.h"
#include"JH/Weapon/WeaponDataAsset.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Ranged / Melee
	WeaponSlots.SetNum(2);

	WeaponSlots[0].MaxCount = 2;
	WeaponSlots[1].MaxCount = 1;

}


void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();


}


void UWeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UWeaponManagerComponent::PickUpWeapon(AWeaponBase* NewWeapon)
{
	if (!NewWeapon || !NewWeapon->GetWeaponData()) return;

	AttachToSocket(NewWeapon, NewWeapon->GetWeaponData()->HolsterSocket);


	UE_LOG(LogTemp, Warning, TEXT("Picked up weapon: %s"), *NewWeapon->GetName());
	//int32 CategoryIndex = (NewWeapon->GetWeaponData()->WeaponCategory == EWeaponType::Ranged) ? 0 : 1;
	//FWeaponSlot& TargetSlot = WeaponSlots[CategoryIndex];

	//if (TargetSlot.Weapons.Num() < TargetSlot.MaxCount)
	//{
	//	TargetSlot.Weapons.Add(NewWeapon);

	//	if (!CurrentWeapon)
	//	{
	//		CurrentWeapon = NewWeapon;
	//		AttachToSocket(NewWeapon, NewWeapon->GetWeaponData()->HandSocket);
	//	}
	//	else
	//	{
	//		AttachToSocket(NewWeapon, NewWeapon->GetWeaponData()->HolsterSocket);
	//	}
	//}
}

void UWeaponManagerComponent::AttachToSocket(AWeaponBase* Weapon, const FName& SocketName)
{

	UE_LOG(LogTemp, Warning, TEXT("Attaching weapon: %s to socket: %s"), *Weapon->GetName(), *SocketName.ToString());
	AActor* Owner = GetOwner();
	// if (!Owner||!CurrentWeapon) return;

	USkeletalMeshComponent* OwnerMesh = Owner->FindComponentByClass<USkeletalMeshComponent>();

	Weapon->SetActorEnableCollision(false);

	FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, true);
	Weapon->AttachToComponent(OwnerMesh, Rules, SocketName);
}
