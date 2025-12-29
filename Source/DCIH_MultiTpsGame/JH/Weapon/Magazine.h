#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JH/Interface/MagazineInterface.h"
#include "Magazine.generated.h"

UCLASS()
class DCIH_MULTITPSGAME_API AMagazine : public AActor
{
	GENERATED_BODY()
	
public:	
	AMagazine();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Components")
	class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Components")
	class USkeletalMeshComponent* MeshComp;
};
