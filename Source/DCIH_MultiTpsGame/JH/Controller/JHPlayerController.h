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
    void CacheCharacter();
	void InitializeUIManager();
    void BindHealthComponentToUI();
    
    // ===== Input Callbacks =====
    void AddDefaultMappingContext();
    void OnMove(const FInputActionValue& Value);
    void OnLook(const FInputActionValue& Value);
    void OnJumpStarted();
    void OnJumpCompleted();
    void OnSprintStarted();
    void OnSprintCompleted();
    void OnAttack();



private:
    TWeakObjectPtr<AJHCharacter> CachedCharacter;

	// ===== UI =====
    UPROPERTY()
    TObjectPtr<class UUIManager> UIManager;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUIManager> UIManagerClass;

    //===== Input =====
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


public:
    float MousePitch = 0.f;
};
