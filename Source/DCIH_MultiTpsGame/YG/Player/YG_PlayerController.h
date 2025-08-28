// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/MT_PlayerController.h"
#include "YG/Interface/YGI_InputSystem.h"
#include "YG_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DCIH_MULTITPSGAME_API AYG_PlayerController : public AMT_PlayerController
                                                   , public IYGI_InputSystem
{
	GENERATED_BODY()

public:
	AYG_PlayerController();

protected:
	virtual void SetupInputComponent() override;
	
public:
	// Interface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	void ClearImc();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	void AddImc(EYG_InputMappingContext ImcIndex, int32 Priority,
	            const FModifyContextOptions& Options = FModifyContextOptions());

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	bool RemoveImc(EYG_InputMappingContext ImcIndex, const FModifyContextOptions& Options = FModifyContextOptions());

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	bool HasImc(EYG_InputMappingContext ImcIndex);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	void ChangeInputModeUiOnly(UUserWidget* TargetWidget, EMouseLockMode InMouseLockMode = EMouseLockMode::DoNotLock,
	                           bool bHideCursorDuringCapture = true);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	UInputMappingContext* GetImc(EYG_InputMappingContext Name);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Input")
	UInputAction* GetIa(EYG_InputAction Name);

protected:
	// Manager
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components", meta=(AllowPrivateAccess=true))
	TObjectPtr<class UYGC_InputSystemManager> InputSystemManager;
};
