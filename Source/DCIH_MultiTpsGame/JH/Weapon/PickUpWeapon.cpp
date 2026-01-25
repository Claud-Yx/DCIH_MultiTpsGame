#include "JH/Weapon/PickUpWeapon.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include"JH/Weapon/WeaponPickUpInterface.h"
#include "JH/Weapon/WeaponDataAsset.h"

APickUpWeapon::APickUpWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(CollisionSphere);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void APickUpWeapon::OnConstruction(const FTransform& Transform)
{
	if (WeaponData && WeaponData->PickupMesh)
		Mesh->SetStaticMesh(WeaponData->PickupMesh);

}

void APickUpWeapon::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickUpWeapon::OnOverlapBegin);

}

void APickUpWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->Implements<UWeaponPickUpInterface>())
	{
		IWeaponPickUpInterface::Execute_PickUpWeapon(OtherActor, WeaponData);
		Destroy();
	}
}

void APickUpWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}