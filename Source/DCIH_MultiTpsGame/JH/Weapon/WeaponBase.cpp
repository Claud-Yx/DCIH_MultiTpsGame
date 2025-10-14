#include "JH/Weapon/WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Pawn.h"

AWeaponBase::AWeaponBase()
{
    mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    SetRootComponent(mesh);

	weaponState = EWeaponState::Idle;
}

void AWeaponBase::BeginPlay()
{
    Super::BeginPlay();

    //if (APawn* P = Cast<APawn>(GetOwner()))
    //{
    //    OwningPawn = P;
    //}
    //else
    //{
    //    OwningPawn.Reset();
    //}
}

void AWeaponBase::SetOwner(AActor* NewOwner)
{
    Super::SetOwner(NewOwner);

    if (APawn* P = Cast<APawn>(NewOwner))
    {
        owningPawn = P;
    }
    else
    {
        owningPawn.Reset();
    }
}