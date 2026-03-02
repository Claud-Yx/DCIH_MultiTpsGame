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

	//CurrentWeapon->GetWeaponData()->Category = EWeaponCategory::None;
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

void UWeaponManagerComponent::SwapWeapon(int32 WeaponNum)
{
    // 1. 입력 번호(1~5)를 슬롯 인덱스로 매핑
    int32 TargetSlotIdx = -1;
    int32 TargetWeaponIdx = 0; // 기본적으로 슬롯의 첫 번째 무기

    switch (WeaponNum)
    {
    case 1: case 2:
        TargetSlotIdx = RANGED_WEAPON; // 0번 슬롯
        TargetWeaponIdx = WeaponNum - 1;
        break;
    case 3:
        TargetSlotIdx = MELEE_WEAPON;  // 1번 슬롯
        break;
    case 4:
        // 만약 슬롯 배열에 GRENADE_SLOT(2) 등을 추가했다면:
        TargetSlotIdx = 2;
        break;
    case 5:
        TargetSlotIdx = 3;
        break;
    default:
        return; // 정의되지 않은 번호는 무시
    }

    // 2. 유효성 검사 (슬롯과 무기가 존재하는지)
    if (!WeaponSlots.IsValidIndex(TargetSlotIdx)) return;

    FWeaponSlot& TargetSlot = WeaponSlots[TargetSlotIdx];
    if (!TargetSlot.Weapons.IsValidIndex(TargetWeaponIdx) || !TargetSlot.Weapons[TargetWeaponIdx])
    {
        UE_LOG(LogTemp, Warning, TEXT("%d번 슬롯에 무기가 없습니다."), WeaponNum);
        return;
    }

    // 3. 현재 무기와 동일하면 스킵
    AWeaponBase* SelectedWeapon = TargetSlot.Weapons[TargetWeaponIdx];
    if (CurrentWeapon == SelectedWeapon) return;

    // 4. 모든 무기 정리 및 부착 로직 (효율적인 범위 기반 루프)
    for (FWeaponSlot& Slot : WeaponSlots)
    {
        for (TObjectPtr<AWeaponBase> Weapon : Slot.Weapons)
        {
            if (Weapon)
            {
                // 일단 모두 홀스터로 (비활성 무기들)
                AttachToSocket(Weapon, Weapon->GetWeaponData()->HolsterSocket);
            }
        }
    }

    // 5. 선택된 무기 활성화
    CurrentWeapon = SelectedWeapon;
    AttachToSocket(CurrentWeapon, CurrentWeapon->GetWeaponData()->HandSocket);

    UE_LOG(LogTemp, Log, TEXT("무기 교체: %s (슬롯 %d)"), *CurrentWeapon->GetName(), TargetSlotIdx);

    //if (!WeaponSlots.IsValidIndex(RANGED_WEAPON)) return;

    //if (WeaponNum == 1 || WeaponNum == 2)
    //{
    //    //CurrentWeapon = WeaponSlots[RANGED_WEAPON].Weapons[WeaponNum-1];
    //    for (int32 i = 0; i < MAX_WEAPON_SLOT; ++i)
    //    {
    //        for (int32 j = 0; j < WeaponSlots[i].MaxCount; ++j)
    //        {
    //            AWeaponBase* TargetWeapon = WeaponSlots[i].Weapons[WeaponNum - 1];
    //            if (TargetWeapon == CurrentWeapon)
    //            {
    //                AttachToSocket(TargetWeapon, TargetWeapon->GetWeaponData()->HandSocket);
    //            }
    //            else
    //            {
    //                AttachToSocket(TargetWeapon, TargetWeapon->GetWeaponData()->HolsterSocket);
				//}
    //        }
    //    }
    //}
}

void UWeaponManagerComponent::AttachToSocket(AWeaponBase* Weapon, const FName& SocketName)
{
	AActor* Owner = GetOwner();
	// if (!Owner||!CurrentWeapon) return;

	USkeletalMeshComponent* OwnerMesh = 
        Owner->FindComponentByClass<USkeletalMeshComponent>();

	Weapon->SetActorEnableCollision(false);

	FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, true);
	Weapon->AttachToComponent(OwnerMesh, Rules, SocketName);
}

EWeaponCategory UWeaponManagerComponent:: GetCurrentWeaponCategory() const
{
    if (!CurrentWeapon) 
        return EWeaponCategory::None;
    else {
        return CurrentWeapon->GetWeaponData()->Category;
    }
};