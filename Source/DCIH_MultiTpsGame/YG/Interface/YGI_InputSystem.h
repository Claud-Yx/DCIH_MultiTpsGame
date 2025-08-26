// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "UObject/Interface.h"
#include "YG/Enum/YGE_InputSystem.h"
#include "YGI_InputSystem.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UYGI_InputSystem : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DCIH_MULTITPSGAME_API IYGI_InputSystem
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Input" )
	void ClearImc();

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Input" )
	void AddImc( EYG_InputMappingContext ImcIndex, int32 Priority, const FModifyContextOptions& Options = FModifyContextOptions() );

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Input" )
	bool RemoveImc( EYG_InputMappingContext ImcIndex, const FModifyContextOptions& Options = FModifyContextOptions() );

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Input" )
	bool HasImc( EYG_InputMappingContext ImcIndex );

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Input" )
	void ChangeInputModeGameOnly( bool bConsumeCaptureMouseDown = true, bool bShowMouseCursor = false );

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Input" )
	void ChangeInputModeUiOnly( UUserWidget* TargetWidget, EMouseLockMode InMouseLockMode = EMouseLockMode::DoNotLock, bool bHideCursorDuringCapture = true );

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Input" )
	UInputMappingContext* GetImc( EYG_InputMappingContext Name );

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Input" )
	UInputAction* GetIa( EYG_InputAction Name );
};
