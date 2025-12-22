#include "JH/Weapon/Magazine.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AMagazine::AMagazine()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp->CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	RootComponent = CollisionComp;
	CollisionComp->InitSphereRadius(30.f);
	CollisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMagazine::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// Use Interface And Can Equip Anybody who Overlap
}
