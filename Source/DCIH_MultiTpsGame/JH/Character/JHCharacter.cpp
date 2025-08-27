#include "JH/Character/JHCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "JH/Weapon/Rifle.h"


#include "JH/Character/JHCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AJHCharacter::AJHCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM(
        TEXT("/Script/Engine.SkeletalMesh'/Game/JHFolder/MyAsset/SKM_Soldier.SKM_Soldier'")); // 실제 경로로 교체
    if (SKM.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(SKM.Object);
    }

    GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -92.f)); 
    GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 350.f;
    SpringArm->bUsePawnControlRotation = true;
    SpringArm->bInheritPitch = true;
    SpringArm->bInheritYaw = true;
    SpringArm->bInheritRoll = false;
    SpringArm->SocketOffset = FVector(0.f, 50.f, 50.f);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false; // 카메라는 붐만 따라감

    bUseControllerRotationYaw = true;   // 컨트롤러 회전 사용
    GetCharacterMovement()->bOrientRotationToMovement = true; // 이동 방향으로 회전
    GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
    ApplySpeed(WalkSpeed);
}

void AJHCharacter::Move(const FVector2D Axis)
{
    if (!Controller) return;

    // 컨트롤러 Yaw 기준 전후좌우 벡터 계산
    const FRotator YawRot(0.f, Controller->GetControlRotation().Yaw, 0.f);
    const FVector Forward = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
    const FVector Right = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

    if (Axis.Y != 0.f) AddMovementInput(Forward, Axis.Y);
    if (Axis.X != 0.f) AddMovementInput(Right, Axis.X);
}

void AJHCharacter::Look(const FVector2D Axis)
{
    // 시점 회전(컨트롤러 회전 → 스프링암 반영 → 카메라 추종)
    if (Axis.X != 0.f) AddControllerYawInput(Axis.X);
    if (Axis.Y != 0.f) AddControllerPitchInput(- Axis.Y);
}

void AJHCharacter::StartJump()
{
    Jump();
}

void AJHCharacter::StopJump()
{
    StopJumping();
}

void AJHCharacter::StartSprint()
{
    ApplySpeed(SprintSpeed);
}

void AJHCharacter::StopSprint()
{
    ApplySpeed(WalkSpeed);

}

void AJHCharacter::Fire()
{

}

void AJHCharacter::BeginPlay()
{
	Super::BeginPlay();

    if (UWorld* World = GetWorld())
    {
        // 라이플 스폰
        EquippedRifle = World->SpawnActor<ARifle>(ARifle::StaticClass());
        if (EquippedRifle)
        {
            EquippedRifle->SetOwner(this);

            EquippedRifle->AttachToComponent(
                GetMesh(),
                FAttachmentTransformRules::SnapToTargetNotIncludingScale,
                TEXT("WeaponSocket")
            );
        }
    }
}

void AJHCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AJHCharacter::ApplySpeed(float NewSpeed)
{
    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->MaxWalkSpeed = NewSpeed;
    }
}

