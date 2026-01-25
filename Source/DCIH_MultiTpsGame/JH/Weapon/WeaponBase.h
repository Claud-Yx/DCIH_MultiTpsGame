#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JH/Enum/E_WeaponState.h"
#include "JH/Interface/InteractTarget.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;
class APawn;

// ============================================

UCLASS(Abstract)
class DCIH_MULTITPSGAME_API AWeaponBase : public AActor, public IInteractTarget
{
    GENERATED_BODY()

public:
    AWeaponBase();

protected:
    virtual void BeginPlay() override;


	// ========== Components ==========
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<class USkeletalMeshComponent> MeshComp;
public:
	UFUNCTION(BlueprintPure, Category = "Components")
    FORCEINLINE USkeletalMeshComponent* GetMesh() const { return MeshComp; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<class USphereComponent> CollisionComp;



	// ========== State ==========
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
    EWeaponState WeaponState;

public:
    UFUNCTION(BlueprintPure, Category = "State")
    FORCEINLINE EWeaponState GetWeaponState() const { return WeaponState; }
    void SetWeaponState(EWeaponState newState) { WeaponState = newState; }

	// ========== Owners ==========
protected:
	UPROPERTY()
	TWeakObjectPtr<class ACharacter> OwnerCharacter;

	UPROPERTY()
	TWeakObjectPtr<class APlayerController> OwnerController;



	// ========== Functions ==========
public:
    // ĳ���Ϳ��� ó��
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void OnEquipped(ACharacter* Character);

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void OnUnEquipped();

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    virtual void OnDropped();

    //UFUNCTION(BlueprintCallable, Category = "Weapon")
    //virtual void Attack();
    virtual void Attack() PURE_VIRTUAL(AWeaponBase::Attack, );



	// ========== Attach&Detach ==========
protected:
    void AttachWeaponToSocket(const FName& SocketName);
    void DetachWeapon();
    void EnablePhysics(bool bEnable);

    UPROPERTY()
    FName WeaponSocketName;


    // virtual void SetOwner(AActor* NewOwner) override;

    // virtual void Attack() {unimplemented();}

};
