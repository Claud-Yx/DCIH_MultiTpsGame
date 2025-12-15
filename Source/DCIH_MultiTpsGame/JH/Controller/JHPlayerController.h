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
    virtual void OnPossess(APawn* InPawn) override;
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    void AddDefaultMappingContext();
	// void InitializeUIManager();
    // void BindHealthComponentToUI();

    void OnMove(const FInputActionValue& Value);
    void OnLook(const FInputActionValue& Value);
    void OnJumpStarted();
    void OnJumpCompleted();
    void OnSprintStarted();
    void OnSprintCompleted();
    void OnAttack();
    
    


public:
    float MousePitch = 0.f;

	class UUIManager* GetUIManager() const { return UIManager; }

private:
    TWeakObjectPtr<AJHCharacter> CachedCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUIManager> UIManagerClass;

    UPROPERTY(EditDefaultsOnly, Category ="UI")
    TObjectPtr<class UUIManager> UIManager;


    
    UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputMappingContext> IMC_Default;

    UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> IA_Move;

    UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> IA_Look;

    UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> IA_Jump;

    UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> IA_Sprint;

    UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> IA_Fire;




    void HandleWeaponEquipped(class AWeaponBase* Weapon);


};
