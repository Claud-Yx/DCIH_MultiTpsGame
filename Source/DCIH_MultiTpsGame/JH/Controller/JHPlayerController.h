// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "JHPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class AJHCharacter;

UCLASS()
class DCIH_MULTITPSGAME_API AJHPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AJHPlayerController();

protected:
    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;
    virtual void SetupInputComponent() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Input|Mapping", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputMappingContext> IMC_Default;

    UPROPERTY(EditDefaultsOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> IA_Move;

    UPROPERTY(EditDefaultsOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> IA_Look;

    UPROPERTY(EditDefaultsOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> IA_Jump;

    UPROPERTY(EditDefaultsOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> IA_Sprint;

    UPROPERTY(EditDefaultsOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> IA_Fire;

    TWeakObjectPtr<AJHCharacter> CachedCharacter;

    // 입력 콜백
    void OnMove(const FInputActionValue& Value);
    void OnLook(const FInputActionValue& Value);
    void OnJumpStarted();
    void OnJumpCompleted();
    void OnSprintStarted();
    void OnSprintCompleted();
	void OnFire();

    void CacheControlledCharacter();
    void AddDefaultMappingContext();
};
