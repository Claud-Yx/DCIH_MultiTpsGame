#include "JH/Weapon/WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Pawn.h"

AWeaponBase::AWeaponBase()
{
    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    SetRootComponent(Mesh);
}

void AWeaponBase::BeginPlay()
{
    Super::BeginPlay();

    if (APawn* P = Cast<APawn>(GetOwner()))
    {
        OwningPawn = P;
    }
    else
    {
        OwningPawn.Reset();
    }
}

void AWeaponBase::SetOwner(AActor* NewOwner)
{
    Super::SetOwner(NewOwner);

    if (APawn* P = Cast<APawn>(NewOwner))
    {
        OwningPawn = P;
    }
    else
    {
        OwningPawn.Reset();
    }
}
