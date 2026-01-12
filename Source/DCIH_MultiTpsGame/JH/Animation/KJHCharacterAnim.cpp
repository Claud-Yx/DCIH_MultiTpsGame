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
	bIsProning = owningCharacter->GetIsProne();

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
//	// OwningCharacter가 없으면 실행 불가
//	if (!owningCharacter) return;
//
//	// 1. "Launch" 노티파이가 들어왔는지 이름으로 확인
//	if (NotifyName == TEXT("Launch"))
//	{
//		FVector Velocity = owningCharacter->GetVelocity();
//
//		// 작성하신 로직 그대로 적용
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
//	// 2. "LaunchStop" 노티파이 확인
//	else if (NotifyName == TEXT("LaunchStop"))
//	{
//		owningCharacter->RollEnd(); // 캐릭터의 정지 함수 호출
//		UE_LOG(LogTemp, Warning, TEXT("Stop Triggered by AnimInstance"));
//	}
//}