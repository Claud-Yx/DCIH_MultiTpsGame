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

   CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
   CollisionComp->SetupAttachment(RootComponent);

   CollisionComp->SetSphereRadius(100.f);
   CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
   CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
   CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

   WeaponState = EWeaponState::UnEquipped;
   // WeaponSocketName = FName("WeaponSocket");
}

void AWeaponBase::BeginPlay()
{
    Super::BeginPlay();

    if (CollisionComp)
    {
        CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnPickupSphereOverlap);
    }
}

UWeaponDataAsset* AWeaponBase::GetWeaponData() const
{
    return WeaponData;
}

void AWeaponBase::OnPickupSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    UWeaponManagerComponent* WeaponManagerComp = OtherActor->FindComponentByClass<UWeaponManagerComponent>();
	if (WeaponManagerComp)
    {
        WeaponManagerComp->PickUpWeapon(this);
        // Destroy();
    }
    
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

 void AWeaponBase::SetOwner(AActor* NewOwner)
 {
     Super::SetOwner(NewOwner);
 
     if (ACharacter* C = Cast<ACharacter>(NewOwner))
     {
         OwnerCharacter = C;
     }
     else
     {
         OwnerCharacter.Reset();
     }
 }

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