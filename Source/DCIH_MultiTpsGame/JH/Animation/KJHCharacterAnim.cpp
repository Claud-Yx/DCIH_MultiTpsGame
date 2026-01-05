#include "JH/Animation/KJHCharacterAnim.h"
#include "JH/Character/JHCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JH/Weapon/WeaponBase.h"

UKJHCharacterAnim::UKJHCharacterAnim()
{
}

void UKJHCharacterAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

    // 최초 캐릭터 캐싱
    if (APawn* Pawn = TryGetPawnOwner())
    {
        owningCharacter = Cast<AJHCharacter>(Pawn);
    }
}

void UKJHCharacterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (!owningCharacter.IsValid()) return;

    AO_Yaw = owningCharacter->GetAO_Yaw();
    AO_Pitch = owningCharacter->GetAO_Pitch();

    speed = owningCharacter->GetVelocity().Size();
    direction = CalculateDirection(owningCharacter->GetVelocity(), owningCharacter->GetActorRotation());
    isInAir = owningCharacter->GetCharacterMovement()->IsFalling();

    characterState = owningCharacter->GetState();

	EquippedWeapon = owningCharacter->GetEquippedWeapon();

	bIsCrouching = owningCharacter->GetIsCrouch();

    if (EquippedWeapon && EquippedWeapon->GetMesh())
    {
        LeftHandTransform = EquippedWeapon->GetMesh()->GetSocketTransform(
            FName("LeftHandSocket"),
            ERelativeTransformSpace::RTS_World);

        FVector OutPosition;
        FRotator OutRotation;

        owningCharacter->GetMesh()->TransformToBoneSpace(
            FName("RightHand"),
            LeftHandTransform.GetLocation(),
            FRotator::ZeroRotator,
            OutPosition,
            OutRotation);

        LeftHandTransform.SetLocation(OutPosition);
        LeftHandTransform.SetRotation(FQuat(OutRotation));
    }

	TurningInPlace = owningCharacter->GetTurningInPlace();

    // 화면 출력
    // FString DebugText = FString::Print(TEXT("Speed: %.2f, Direction: %.2f"), speed, direction);
    // UKismetSystemLibrary::PrintString(this, DebugText, true, true, FLinearColor::Yellow, 0.f);
}

void UKJHCharacterAnim::PlayFireMontage()
{
	Montage_Play(fireMontage);
}

void UKJHCharacterAnim::PlayReloadMontage()
{
	Montage_Play(ReloadMontage);
	UE_LOG(LogTemp, Warning, TEXT("Reload Montage Played"));
}

void UKJHCharacterAnim::PlayRollMontage()
{
    Montage_Play(RollMontage);
}