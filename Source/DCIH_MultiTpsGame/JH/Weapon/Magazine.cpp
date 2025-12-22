#include "JH/Weapon/Magazine.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"

AMagazine::AMagazine()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	RootComponent = CollisionComp;
	CollisionComp->InitSphereRadius(30.f);
	CollisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMagazine::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->Implements<UAmmoPickUpInterface>())
	{
		IAmmoPickUpInterface::Execute_AddMagazine(OtherActor, 1);
		Destroy();
	}
	// Use Interface And Can Equip Anybody who Overlap
}