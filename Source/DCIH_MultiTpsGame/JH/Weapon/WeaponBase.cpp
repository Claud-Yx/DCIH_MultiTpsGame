#include "JH/Weapon/WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "JH/Interface/InteractTarget.h"
#include "JH/Weapon/WeaponDataAsset.h"
#include "JH/Components/WeaponManagerComponent.h"

// IMPLEMENT_PURE_VIRTUAL(AWeaponBase, Attack, );

AWeaponBase::AWeaponBase()
{
    PrimaryActorTick.bCanEverTick = true;

    MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
    SetRootComponent(MeshComp);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

   PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
   PickupSphere->SetupAttachment(RootComponent);
   PickupSphere->SetSphereRadius(100.f);
   PickupSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
   PickupSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
   PickupSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

   WeaponState = EWeaponState::UnEquipped;
   // WeaponSocketName = FName("WeaponSocket");
}


void AWeaponBase::BeginPlay()
{
    Super::BeginPlay();

    PickupSphere->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnOverlapBegin);
}

void AWeaponBase::SetOwner(AActor* NewOwner)
{
    Super::SetOwner(NewOwner);
    OwnerCharacter = Cast<ACharacter>(NewOwner);

    //if (ACharacter* C = Cast<ACharacter>(NewOwner))
    //{
    //    OwnerCharacter = C;
    //}
    //else
    //{
    //    OwnerCharacter.Reset();
    //}
}

void AWeaponBase::SetOwnerController(APlayerController* Controller)
{
    OwnerController = Controller;
}

void AWeaponBase::OnEquip(ACharacter* NewOwner)
{
    if (!NewOwner) return;

    // Owner 등록
    SetOwner(NewOwner);
    SetOwnerController(Cast<APlayerController>(NewOwner->GetController()));

    // 물리 / 콜리전 정리
    EnablePhysics(false);
    PickupSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    SetWeaponState(EWeaponState::Equipped);
}

void AWeaponBase::OnUnEquip()
{
    SetWeaponState(EWeaponState::Holstered);
}

void AWeaponBase::OnDrop()
{
    DetachFromOwner();
    EnablePhysics(true);

    PickupSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    SetWeaponState(EWeaponState::UnEquipped);

    OwnerCharacter.Reset();
    OwnerController.Reset();
}
//void AWeaponBase::OnUnEquipped()
//{
//    SetWeaponState(EWeaponState::UnEquipped);
//    OwnerCharacter = nullptr;
//    OwnerController = nullptr;
//}
//
//void AWeaponBase::OnDropped()
//{
//    SetWeaponState(EWeaponState::UnEquipped);
//    DetachWeapon();
//    EnablePhysics(true);
//
//    // Enable pickup collision
//    if (CollisionComp)
//    {
//        CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
//    }
//
//    OwnerCharacter = nullptr;
//    OwnerController = nullptr;
//}
//
//void AWeaponBase::DetachWeapon()
//{
//    FDetachmentTransformRules DetachRules(EDetachmentRule::KeepWorld, true);
//    DetachFromActor(DetachRules);
//}

void AWeaponBase::AttachToSocket(const FName& SocketName)
{
    if (!OwnerCharacter.IsValid() || SocketName == NAME_None) return;

    FAttachmentTransformRules Rules
    (
        EAttachmentRule::SnapToTarget,
        EAttachmentRule::SnapToTarget,
        EAttachmentRule::KeepWorld,
        true
    );
    AttachToComponent(OwnerCharacter->GetMesh(), Rules, SocketName);
}
void AWeaponBase::DetachFromOwner()
{
    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
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


void AWeaponBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("Weapon Overlapped with: %s"), *OtherActor->GetName());
 //   UWeaponManagerComponent* WeaponManagerComp = OtherActor->FindComponentByClass<UWeaponManagerComponent>();
	//if (WeaponManagerComp)
 //   {
 //       WeaponManagerComp->PickUpWeapon(this);
 //       // Destroy();
 //   }
    
}


//void AWeaponBase::OnEquipped(ACharacter* Character)
//{
//    if (!Character) return;
//
//    OwnerCharacter = Character;
//    SetOwner(Character);
//    
//    OwnerController = Cast<APlayerController>(Character->GetController());
//
//    EnablePhysics(false);
//
//    if (CollisionComp)
//    {
//        CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//    }
//    AttachWeaponToSocket(WeaponSocketName);
//    SetWeaponState(EWeaponState::Equipped);
//
//    // SetActorTickEnabled(true);
//}
//void AWeaponBase::AttachWeaponToSocket(const FName& SocketName)
//{
//    if (!OwnerCharacter.Get() || !MeshComp) return;
//
//    FAttachmentTransformRules AttachRules(
//        EAttachmentRule::SnapToTarget,
//        EAttachmentRule::SnapToTarget,
//        EAttachmentRule::KeepWorld,
//        true
//    );
//
//    AttachToComponent(OwnerCharacter->GetMesh(), AttachRules, SocketName);
//}
//
//
//
//void AWeaponBase::EnablePhysics(bool bEnable)
//{
//    if (!MeshComp) return;
//
//    if (bEnable)
//    {
//        MeshComp->SetSimulatePhysics(true);
//        MeshComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
//        MeshComp->SetCollisionResponseToAllChannels(ECR_Block);
//    }
//    else
//    {
//        MeshComp->SetSimulatePhysics(false);
//        MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//        MeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
//    }
//}