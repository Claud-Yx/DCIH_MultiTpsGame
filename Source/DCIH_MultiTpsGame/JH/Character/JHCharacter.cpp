#include "JH/Character/JHCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "JH/Weapon/WeaponBase.h"
#include "JH/Weapon/RangedWeaponBase.h"
#include "JH/Components/HealthComponent.h"
#include "JH/Animation/KJHCharacterAnim.h"
#include "JH/UI/UIManager.h"
#include "Kismet/KismetMathLibrary.h"





#include "JH/Character/JHCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AJHCharacter::AJHCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	InitializeCharacter();
	InitializeCamera();

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));

	WalkSpeed = 400.f;
	SprintSpeed = 700.f;
	CurrentState = ECharacterState::Idle;
	TurningInPlace = ETurnInPlace::ETIP_NotTurning;
	AO_Yaw = 0.f;
	AO_Pitch = 0.f;
	InterpAO_Yaw = 0.f;
}

void AJHCharacter::BeginPlay()
{
	Super::BeginPlay();

	StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
	
	InitializeWeapon();
}

void AJHCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculateAimOffset(DeltaTime);

	if (GetVelocity().Size() <= 5.f)
	{
		SetState(ECharacterState::Idle);
	}

	// UE_LOG(LogTemp, Warning, TEXT("Velocity SizeSquared : %f"), GetVelocity().Size());

	// 출력
	//FString StateName = UEnum::GetValueAsString(CurrentState);
	//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("State : %s"), *StateName));

}

void AJHCharacter::InitializeCharacter()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM(
		TEXT("/Script/Engine.SkeletalMesh'/Game/JHFolder/MyAsset/SKM_Soldier.SKM_Soldier'")); // 실제 경로로 교체
	if (SKM.Succeeded())
		GetMesh()->SetSkeletalMesh(SKM.Object);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -92.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bUseControllerRotationYaw = true;   // 컨트롤러 회전 사용
	GetCharacterMovement()->bOrientRotationToMovement = false; // 이동 방향으로 회전
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

	ApplySpeed(WalkSpeed);
}

void AJHCharacter::InitializeCamera()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 350.f;
	SpringArmComp->bUsePawnControlRotation = true;
	//SpringArm->bInheritPitch = true;
	//SpringArm->bInheritYaw = true;
	//SpringArm->bInheritRoll = false;
	SpringArmComp->SocketOffset = FVector(0.f, 50.f, 50.f);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	// Camera->bUsePawnControlRotation = false; // 카메라는 붐만 따라감
}

void AJHCharacter::EquipWeapon(AWeaponBase* Weapon)
{
	if (!Weapon) return;

	// Unequip current weapon
	if (EquippedWeapon)
	{
		UnEquipWeapon();
	}

	EquippedWeapon = Weapon;
	EquippedWeapon->Equip(this);
}

void AJHCharacter::UnEquipWeapon()
{
	if (!EquippedWeapon) return;

	EquippedWeapon->UnEquip();
	EquippedWeapon = nullptr;
}

void AJHCharacter::DropWeapon()
{
	if (!EquippedWeapon) return;

	EquippedWeapon->Drop();
	EquippedWeapon = nullptr;
}

void AJHCharacter::InitializeWeapon()
{
	if (UWorld* World = GetWorld())
	{
		// 라이플 스폰
		EquippedWeapon = World->SpawnActor<AWeaponBase>(WeaponClass);

		AWeaponBase* SpawnedWeapon = World->SpawnActor<AWeaponBase>(WeaponClass);
		if (SpawnedWeapon)
		{
			EquipWeapon(SpawnedWeapon);
		}

		if (EquippedWeapon)
		{
			EquippedWeapon->SetOwner(this);

			EquippedWeapon->AttachToComponent(
				GetMesh(),
				FAttachmentTransformRules::SnapToTargetNotIncludingScale,
				TEXT("WeaponSocket")
			);
		}
	}
}

void AJHCharacter::Move(const FVector2D& Axis)
{
	if (!Controller) return;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(RightVector, Axis.X);
	AddMovementInput(ForwardVector, Axis.Y);

	if (Axis.SizeSquared() > 0.f)
	{
		if (CurrentState != ECharacterState::Running)
			SetState(ECharacterState::Walking);
	}
	else
	{
		SetState(ECharacterState::Idle);
	}
}

void AJHCharacter::Look(const FVector2D& Axis)
{
	if (Axis.X != 0.f) AddControllerYawInput(Axis.X);
	if (Axis.Y != 0.f) AddControllerPitchInput(-Axis.Y);
}

void AJHCharacter::StartJump()
{
	Jump();
	SetState(ECharacterState::Jumping);
}

void AJHCharacter::StopJump()
{
	StopJumping();
	SetState(ECharacterState::Idle);
}

void AJHCharacter::StartSprint()
{
	ApplySpeed(SprintSpeed);
	SetState(ECharacterState::Running);

	// 컨트롤러 Yaw는 무시, 캐릭터는 이동 방향으로 회전, 
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 카메라는 그대로 마우스 회전 허용
	SpringArmComp->bUsePawnControlRotation = true;
	
	UE_LOG(LogTemp, Warning, TEXT("Sprint Mode → Yaw: %s, Orient: %s"),
		bUseControllerRotationYaw ? TEXT("true") : TEXT("false"),
		GetCharacterMovement()->bOrientRotationToMovement ? TEXT("true") : TEXT("false"));
}

void AJHCharacter::StopSprint()
{
	ApplySpeed(WalkSpeed);
	SetState(ECharacterState::Idle);

	// 다시 캐릭터가 마우스 방향 따라 회전
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void AJHCharacter::CalculateAimOffset(float DeltaTime)
{
	 FVector Velocity = GetVelocity();
	 Velocity.Z = 0;
	float Speed = Velocity.Size();
	// bool bIsInAir = GetCharacterMovement()->IsFalling();

	//if (Speed == 0.f && !bIsInAir) // 정지 상태
	if (CurrentState == ECharacterState::Idle || (CurrentState == ECharacterState::Shooting && Speed == 0.f))
	{
		FRotator CurrentAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		FRotator DeltaAimRotation = UKismetMathLibrary::NormalizedDeltaRotator(StartingAimRotation, CurrentAimRotation);
		AO_Yaw = -DeltaAimRotation.Yaw;
		if (TurningInPlace == ETurnInPlace::ETIP_NotTurning)
		{
			InterpAO_Yaw = AO_Yaw;
		}
		bUseControllerRotationYaw = false;
		// GetCharacterMovement()->bOrientRotationToMovement = false; // 이동 방향으로 회전
		TurnInPlace(DeltaTime);
	}

	// if (Speed > 0.f || bIsInAir)
	if(CurrentState == ECharacterState::Walking)
	{
		StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		AO_Yaw = 0.f;
		bUseControllerRotationYaw = true;
		//GetCharacterMovement()->bOrientRotationToMovement = true; // 이동 방향으로 회전
	}
	else if (CurrentState == ECharacterState::Running) 
	{
		bUseControllerRotationPitch = false;
	}

	AO_Pitch = GetBaseAimRotation().Pitch;
}

void AJHCharacter::Attack()
{
	if (!CanFire()) return;

	auto anim = Cast<UKJHCharacterAnim>(GetMesh()->GetAnimInstance());
	anim->PlayFireMontage();

	if (EquippedWeapon)
	{
		EquippedWeapon->Attack();

		SetState(ECharacterState::Shooting);
	}
}

void AJHCharacter::SetState(ECharacterState NewState)
{
	if (CurrentState == NewState) return;

	CurrentState = NewState;

}

bool AJHCharacter::CanFire() const
{
	// 전역 컨테이너
	static const TSet<ECharacterState> FireAllowedStates =
	{
		ECharacterState::Idle,
		ECharacterState::Walking,
		ECharacterState::Shooting
	};
	return FireAllowedStates.Contains(CurrentState);
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

void AJHCharacter::TurnInPlace(float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("AO_Yaw : %f"), AO_Yaw);
	// UE_LOG(LogTemp, Warning, TEXT("TurningInPlace : %d"), (uint8)TurningInPlace);

	if (AO_Yaw > 90.f)
	{
		TurningInPlace = ETurnInPlace::ETIP_Right;
	}
	else if (AO_Yaw<-90.f)
	{
		TurningInPlace = ETurnInPlace::ETIP_Left;
	}

	if (TurningInPlace != ETurnInPlace::ETIP_NotTurning)
	{
		FRotator CurrentRotation = GetActorRotation();
		FRotator TargetRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);

		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 4.f);

		SetActorRotation(NewRotation);

		InterpAO_Yaw = FMath::FInterpTo(InterpAO_Yaw, 0.f, DeltaTime, 4.f);
		AO_Yaw = InterpAO_Yaw;

		float DeltaYaw = FMath::Abs(FMath::FindDeltaAngleDegrees(CurrentRotation.Yaw, TargetRotation.Yaw));
		if (DeltaYaw < 5.f)
		{
			TurningInPlace = ETurnInPlace::ETIP_NotTurning;
			StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
			AO_Yaw = 0.f;
			InterpAO_Yaw = 0.f;
		}
	}
}

void AJHCharacter::ApplyDamages(float damageAmount)
{
	// curHealth -= 10.f;
	// healthPercent = curHealth / maxHealth;

	HealthComp->ApplyDamage(damageAmount);

}

void AJHCharacter::Heal(float healAmount)
{
	HealthComp->Heal(healAmount);
}