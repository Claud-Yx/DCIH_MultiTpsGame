#include "JH/Components/WeaponManagerComponent.h"
#include "JH/Weapon/WeaponBase.h"
#include "JH/Enum/E_WeaponTypes.h"
#include "JH/Weapon/WeaponDataAsset.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Ranged / Melee
	WeaponSlots.SetNum(MAX_WEAPON_SLOT);

	WeaponSlots[RANGED_WEAPON].MaxCount = 2;
	WeaponSlots[MELEE_WEAPON].MaxCount = 1;
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
    if (!NewWeapon || !NewWeapon->GetWeaponData())
    {
        UE_LOG(LogTemp, Error, TEXT("PickUpWeapon: NewWeapon or Data is Null!"));
        return;
    }

    const EWeaponCategory Category = NewWeapon->GetWeaponData()->Category;

    const int32 TargetIndex = (Category == EWeaponCategory::Ranged) ? RANGED_WEAPON : MELEE_WEAPON;
    FWeaponSlot& TargetSlot = WeaponSlots[TargetIndex];

    if (TargetSlot.Weapons.Num() >= TargetSlot.MaxCount)
    {
        return;
    }

    TargetSlot.Weapons.Add(NewWeapon);
    NewWeapon->SetOwner(GetOwner());

    if (!CurrentWeapon)
    {
        CurrentWeapon = NewWeapon;
        AttachToSocket(NewWeapon, NewWeapon->GetWeaponData()->HandSocket);
    }
    else
    {
        AttachToSocket(NewWeapon, NewWeapon->GetWeaponData()->HolsterSocket);
    }

    NewWeapon->SetActorEnableCollision(false);
}

void UWeaponManagerComponent::DropCurrentWeapon()
{
}

void UWeaponManagerComponent::SwapWeapon()
{
}

void UWeaponManagerComponent::AttachToSocket(AWeaponBase* Weapon, const FName& SocketName)
{
	AActor* Owner = GetOwner();
	// if (!Owner||!CurrentWeapon) return;

	USkeletalMeshComponent* OwnerMesh = Owner->FindComponentByClass<USkeletalMeshComponent>();

	Weapon->SetActorEnableCollision(false);

	FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, true);
	Weapon->AttachToComponent(OwnerMesh, Rules, SocketName);
}