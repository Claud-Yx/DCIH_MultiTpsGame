#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;
class APawn;

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
    Idle,
    Using,
    Reloading,
    Equipping
};

UCLASS()
class DCIH_MULTITPSGAME_API AWeaponBase : public AActor
{
    GENERATED_BODY()

public:
    AWeaponBase();

    UFUNCTION(BlueprintPure, Category = "Weapon|State")
    EWeaponState GetWeaponState() const { return WeaponState; }
    
    virtual void SetOwner(AActor* NewOwner) override;

protected:
    virtual void BeginPlay() override;


    void SetWeaponState(EWeaponState NewState) { WeaponState = NewState; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* Mesh;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Weapon|State")
    EWeaponState WeaponState = EWeaponState::Idle;

    TWeakObjectPtr<APawn> OwningPawn;
};
