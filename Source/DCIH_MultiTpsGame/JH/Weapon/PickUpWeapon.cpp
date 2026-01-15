

#include "JH/Weapon/PickUpWeapon.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

APickUpWeapon::APickUpWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(CollisionSphere);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void APickUpWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickUpWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUpWeapon::Interact_Implementation(AActor* Interactor)
{
}

