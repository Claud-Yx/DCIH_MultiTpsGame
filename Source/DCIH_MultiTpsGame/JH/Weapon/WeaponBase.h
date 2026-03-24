#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JH/Enum/E_WeaponState.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;
class APawn;
class UWeaponDataAsset;
// ============================================

UCLASS(Abstract)
class DCIH_MULTITPSGAME_API AWeaponBase : public AActor
{
    GENERATED_BODY()

public:
    AWeaponBase();

    virtual void Attack() PURE_VIRTUAL(AWeaponBase::Attack, );

    UFUNCTION(BlueprintPure, Category = "Data")
    UWeaponDataAsset* GetWeaponData() const;
    
    UFUNCTION(BlueprintPure, Category = "Components")
    FORCEINLINE USkeletalMeshComponent* GetMesh() const { return MeshComp; }

    UFUNCTION(BlueprintPure, Category = "State")
    FORCEINLINE EWeaponState GetWeaponState() const { return WeaponState; }

    UFUNCTION(BlueprintCallable, Category = "Weapon|State")
    void SetWeaponState(EWeaponState NewState) { WeaponState = NewState; }

    void SetOwnerController(class APlayerController* Controller);

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnPickupSphereOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );
	// ========== Components ==========
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<class USkeletalMeshComponent> MeshComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<class USphereComponent> CollisionComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UWeaponDataAsset> WeaponData;

    UPROPERTY(BlueprintReadOnly, Category = "Owner")
    TWeakObjectPtr<class ACharacter> OwnerCharacter;

    UPROPERTY(BlueprintReadOnly, Category = "Owner")
    TWeakObjectPtr<class APlayerController> OwnerController;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    EWeaponState WeaponState;


	// ========== State ==========
//public:
//
//    void SetWeaponState(EWeaponState newState) { WeaponState = newState; }
//
//	// ========== Owners ==========
//protected:
	// ========== Functions ==========
public:
//    // ĳ���Ϳ��� ó��
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void OnEquipped(ACharacter* Character);

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void OnUnEquipped();

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void OnDropped();
    //UFUNCTION(BlueprintCallable, Category = "Weapon")
    //virtual void Attack();
	//  ========== Attach&Detach ==========
protected:
    void AttachWeaponToSocket(const FName& SocketName);
    void DetachWeapon();
    void EnablePhysics(bool bEnable);
    UPROPERTY()
    FName WeaponSocketName;
public:
     virtual void SetOwner(AActor* NewOwner) override;
     // virtual void Attack() {unimplemented();}

};
