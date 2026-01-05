#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "JH/Character/JHCharacter.h"
#include "JH/Enum/E_TurnInPlace.h"
#include "KJHCharacterAnim.generated.h"

class AJHCharacter;

UCLASS()
class DCIH_MULTITPSGAME_API UKJHCharacterAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
    UKJHCharacterAnim();

    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anim")
    TWeakObjectPtr<AJHCharacter> owningCharacter;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
    ECharacterState characterState;

    UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Movement")
    float speed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    float direction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    bool isInAir;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AimOffset")
    float AO_Yaw;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AimOffset")
    float AO_Pitch;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TurningInPlace")
	ETurnInPlace TurningInPlace;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerAnim")
    TObjectPtr<class UAnimMontage> fireMontage;

    UPROPERTY(EditAnywhere, Category = "Montage")
    TObjectPtr<class UAnimMontage> ReloadMontage;

    UPROPERTY(EditAnywhere, Category = "Montage")
    TObjectPtr<class UAnimMontage> RollMontage;

    TObjectPtr<class AWeaponBase> EquippedWeapon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crouch")
	bool bIsCrouching;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerAnim")
    FTransform LeftHandTransform;

	FTransform GetLeftHandTransform() const { return LeftHandTransform; }

public:
	void PlayFireMontage();

	void PlayReloadMontage();

	void PlayRollMontage();
};