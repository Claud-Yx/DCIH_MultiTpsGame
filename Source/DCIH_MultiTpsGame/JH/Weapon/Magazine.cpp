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
	if (OtherActor->Implements<UMagazineInterface>())
	{
		// UAmmoPickUpInterface::Execute_AddMagazine(OtherActor);
		IMagazineInterface::Execute_AddMagazine(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("MagazineNum") );

		Destroy();
	}
	// Use Interface And Can Equip Anybody who Overlap
}