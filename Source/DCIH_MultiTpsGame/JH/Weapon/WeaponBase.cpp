#include "JH/Weapon/WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "JH/Interface/InteractTarget.h"
#include "JH/Weapon/WeaponDataAsset.h"

// IMPLEMENT_PURE_VIRTUAL(AWeaponBase, Attack, );

AWeaponBase::AWeaponBase()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
    SetRootComponent(MeshComp);

   CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
   CollisionComp->SetupAttachment(RootComponent);

   CollisionComp->SetSphereRadius(100.f);
   CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
   CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
   CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

   WeaponState = EWeaponState::UnEquipped;
   WeaponSocketName = FName("WeaponSocket");
}

void AWeaponBase::BeginPlay()
{
    Super::BeginPlay();
}

UWeaponDataAsset* AWeaponBase::GetWeaponData() const
{
    return WeaponData;
}

void AWeaponBase::OnPickupSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->Implements<UInteractTarget>())
    {
        IInteractTarget::Execute_OnInteract(this, this);
        Destroy();
    }
    //// UCombatComponent* CombatComp = OtherActor->FindComponentByClass<UCombatComponent>();
    //if (CombatComp)
    //{
    //    // 2. ������Ʈ���� "���� ��������"�� ���
    //    // (��, �ڵ� �ݱ��̹Ƿ� �� á�� �� ���� ��ü�� ���� �ʴ� �� �Ϲ����Դϴ�)
    //    CombatComp->EquipWeapon(this);
    //}
    
}


void AWeaponBase::OnEquipped(ACharacter* Character)
{
    if (!Character) return;

    OwnerCharacter = Character;
    SetOwner(Character);
    
    OwnerController = Cast<APlayerController>(Character->GetController());

    EnablePhysics(false);

    if (CollisionComp)
    {
        CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
    AttachWeaponToSocket(WeaponSocketName);
    SetWeaponState(EWeaponState::Equipped);

    // SetActorTickEnabled(true);
}

void AWeaponBase::AttachWeaponToSocket(const FName& SocketName)
{
    if (!OwnerCharacter.Get() || !MeshComp) return;

    FAttachmentTransformRules AttachRules(
        EAttachmentRule::SnapToTarget,
        EAttachmentRule::SnapToTarget,
        EAttachmentRule::KeepWorld,
        true
    );

    AttachToComponent(OwnerCharacter->GetMesh(), AttachRules, SocketName);
}

// void AWeaponBase::SetOwner(AActor* NewOwner)
// {
//     Super::SetOwner(NewOwner);
// 
//     if (APawn* P = Cast<APawn>(NewOwner))
//     {
//         OwnerCharacter = P;
//     }
//     else
//     {
//         OwnerCharacter.Reset();
//     }
// }

void AWeaponBase::OnUnEquipped()
{
    SetWeaponState(EWeaponState::UnEquipped);
    OwnerCharacter = nullptr;
    OwnerController = nullptr;
}

void AWeaponBase::OnDropped()
{
    SetWeaponState(EWeaponState::UnEquipped);
    DetachWeapon();
    EnablePhysics(true);

    // Enable pickup collision
    if (CollisionComp)
    {
        CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    }

    OwnerCharacter = nullptr;
    OwnerController = nullptr;
}

void AWeaponBase::DetachWeapon()
{
    FDetachmentTransformRules DetachRules(EDetachmentRule::KeepWorld, true);
    DetachFromActor(DetachRules);
}

void AWeaponBase::EnablePhysics(bool bEnable)
{
    if (!MeshComp) return;

    if (bEnable)
    {
        MeshComp->SetSimulatePhysics(true);
        MeshComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
        MeshComp->SetCollisionResponseToAllChannels(ECR_Block);
    }
    else
    {
        MeshComp->SetSimulatePhysics(false);
        MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        MeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
    }
}