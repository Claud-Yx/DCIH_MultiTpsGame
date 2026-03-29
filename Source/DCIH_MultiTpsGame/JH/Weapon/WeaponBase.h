#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JH/Enum/E_WeaponState.h"
#include "WeaponBase.generated.h"

class UWeaponDataAsset;
class USkeletalMeshComponent;
class APawn;
class USphereComponent;
// ============================================

UCLASS(Abstract)
class DCIH_MULTITPSGAME_API AWeaponBase : public AActor
{
    GENERATED_BODY()

public:
    AWeaponBase();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Attack() PURE_VIRTUAL(AWeaponBase::Attack, );

    virtual void OnEquip(ACharacter* NewOwner);
    virtual void OnUnEquip();
    virtual void OnDrop();
    


    UFUNCTION(BlueprintPure, Category = "Data")
    UWeaponDataAsset* GetWeaponData() const { return WeaponData; }
    
    UFUNCTION(BlueprintPure, Category = "Components")
    FORCEINLINE USkeletalMeshComponent* GetMesh() const { return MeshComp; }

    UFUNCTION(BlueprintPure, Category = "State")
    FORCEINLINE EWeaponState GetWeaponState() const { return WeaponState; }

    FORCEINLINE ACharacter* GetOwnerCharacter() const { return OwnerCharacter.Get(); }
    FORCEINLINE APlayerController* GetOwnerController() const { return OwnerController.Get(); }

    void SetOwnerController(APlayerController* Controller);
    
    virtual void SetOwner(AActor* NewOwner) override;



protected:
    void AttachToSocket(const FName& SocketName);
    void DetachFromOwner();
    void EnablePhysics(bool bEnable);

    FORCEINLINE void SetWeaponState(EWeaponState NewState) { WeaponState = NewState; }


    // virtual void BeginPlay() override;

    UFUNCTION()
    void OnOverlapBegin
    (
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

protected:
	// ========== Components ==========
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<class USkeletalMeshComponent> MeshComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USphereComponent> PickupSphere;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UWeaponDataAsset> WeaponData;



    UPROPERTY(BlueprintReadOnly, Category = "Owner")
    TWeakObjectPtr<class ACharacter> OwnerCharacter;

    UPROPERTY(BlueprintReadOnly, Category = "Owner")
    TWeakObjectPtr<class APlayerController> OwnerController;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    EWeaponState WeaponState = EWeaponState::UnEquipped;

//public:
//    UFUNCTION(BlueprintCallable, Category = "Weapon")
//    virtual void OnEquipped(ACharacter* Character);
//
//    UFUNCTION(BlueprintCallable, Category = "Weapon")
//    virtual void OnUnEquipped();
//
//    UFUNCTION(BlueprintCallable, Category = "Weapon")
//    virtual void OnDropped();

protected:
    //void AttachWeaponToSocket(const FName& SocketName);
    //void DetachWeapon();
    //void EnablePhysics(bool bEnable);
//    UPROPERTY()
//    FName WeaponSocketName;
//
//public:
//     virtual void SetOwner(AActor* NewOwner) override;
};
