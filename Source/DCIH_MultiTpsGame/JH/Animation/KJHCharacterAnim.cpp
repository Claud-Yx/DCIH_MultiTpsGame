#include "JH/Animation/KJHCharacterAnim.h"
#include "JH/Character/JHCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JH/Components/WeaponManagerComponent.h"
#include "JH/Weapon/WeaponBase.h"

UKJHCharacterAnim::UKJHCharacterAnim()
{
}

void UKJHCharacterAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

    // ���� ĳ���� ĳ��
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


    CurrentWeapon = owningCharacter->GetCurrentWeapon();

	bIsCrouching = owningCharacter->GetIsCrouch();
	bIsProning = owningCharacter->GetIsProne();

    if (CurrentWeapon && CurrentWeapon->GetMesh())
    {
        LeftHandTransform = CurrentWeapon->GetMesh()->GetSocketTransform
        (
            FName("LeftHandSocket"),
            ERelativeTransformSpace::RTS_World
        );

        FVector OutPosition;
        FRotator OutRotation;

        owningCharacter->GetMesh()->TransformToBoneSpace
        (
            FName("RightHand"),
            LeftHandTransform.GetLocation(),
            FRotator::ZeroRotator,
            OutPosition,
            OutRotation
        );

        LeftHandTransform.SetLocation(OutPosition);
        LeftHandTransform.SetRotation(FQuat(OutRotation));
    }

	TurningInPlace = owningCharacter->GetTurningInPlace();

    CurrentWeaponCategory = GetEquippedWeaponCategory();
    
    // ȭ�� ���
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

//void UKJHCharacterAnim::AnimNotify_Launch()
//{
//	// owningCharacter->Roll();
//	FVector Velocity = owningCharacter->GetVelocity();
//
//	if (Velocity.SizeSquared() > 10.0f)
//	{
//		FVector LaunchDir = Velocity.GetSafeNormal();
//		owningCharacter->LaunchCharacter(LaunchDir * 1000.0f, true, true);
//	}
//	else
//	{
//		owningCharacter->LaunchCharacter(owningCharacter->GetActorForwardVector() * 1000.0f, true, true);
//	}
//    UE_LOG(LogTemp, Warning, TEXT("Launch Anim Notify Triggered"));
//
//}
//
//void UKJHCharacterAnim::AnimNotify_LaunchStop()
//{
//	owningCharacter->RollEnd();
//	UE_LOG(LogTemp, Warning, TEXT("Launch Stop Anim Notify Triggered"));
//	// owningCharacter->GetCharacterMovement()->StopMovementImmediately();
//}
//
//void UKJHCharacterAnim::NativePlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
//{
//	Super::NativePlayMontageNotifyBegin(NotifyName, BranchingPointNotifyPayload);
//
//	// OwningCharacter�� ������ ���� �Ұ�
//	if (!owningCharacter) return;
//
//	// 1. "Launch" ��Ƽ���̰� ���Դ��� �̸����� Ȯ��
//	if (NotifyName == TEXT("Launch"))
//	{
//		FVector Velocity = owningCharacter->GetVelocity();
//
//		// �ۼ��Ͻ� ���� �״�� ����
//		if (Velocity.SizeSquared() > 10.0f)
//		{
//			FVector LaunchDir = Velocity.GetSafeNormal();
//			owningCharacter->LaunchCharacter(LaunchDir * 1000.0f, true, true);
//		}
//		else
//		{
//			owningCharacter->LaunchCharacter(owningCharacter->GetActorForwardVector() * 1000.0f, true, true);
//		}
//
//		UE_LOG(LogTemp, Warning, TEXT("Launch Triggered by AnimInstance"));
//	}
//	// 2. "LaunchStop" ��Ƽ���� Ȯ��
//	else if (NotifyName == TEXT("LaunchStop"))
//	{
//		owningCharacter->RollEnd(); // ĳ������ ���� �Լ� ȣ��
//		UE_LOG(LogTemp, Warning, TEXT("Stop Triggered by AnimInstance"));
//	}
//}