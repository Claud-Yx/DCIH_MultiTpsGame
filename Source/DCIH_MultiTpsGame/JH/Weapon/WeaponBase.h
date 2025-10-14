#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;
class APawn;

// 파일로 따로
// ============================================
UENUM(BlueprintType)
enum class EWeaponState : uint8
{
    Idle,
    Firing,
    Reloading
};

// ============================================

UCLASS(Abstract)
class DCIH_MULTITPSGAME_API AWeaponBase : public AActor
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<class USkeletalMeshComponent> mesh;

    //굳이. 다른 방법
    UPROPERTY()
    TWeakObjectPtr<APawn> owningPawn;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "State")
    EWeaponState weaponState = EWeaponState::Idle;




protected:

    AWeaponBase();

    virtual void BeginPlay() override;

    
    UFUNCTION(BlueprintPure, Category = "State")
    EWeaponState GetWeaponState() const { return weaponState; }
    
    void SetWeaponState(EWeaponState newState) { weaponState = newState; }

public:
    virtual void SetOwner(AActor* NewOwner) override;

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void Use() PURE_VIRTUAL(AWeaponBase::Use, );

	FORCEINLINE USkeletalMeshComponent* GetMesh() const { return mesh; }
};
