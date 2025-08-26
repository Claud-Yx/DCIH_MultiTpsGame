// Fill out your copyright notice in the Description page of Project Settings.


#include "YG/Player/YGAnim_PlayerCharacter.h"
#include "YG_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UYGAnim_PlayerCharacter::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PlayerCharacter = Cast<AYG_PlayerCharacter>(GetOwningActor());
}

void UYGAnim_PlayerCharacter::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if ( PlayerCharacter )
	{
		auto Movement = PlayerCharacter->GetCharacterMovement();

		Speed = Movement->Velocity.Length();
		MovingDirection = FRotator::MakeFromEuler(Movement->Velocity.GetSafeNormal()).Yaw;
	}  
}
