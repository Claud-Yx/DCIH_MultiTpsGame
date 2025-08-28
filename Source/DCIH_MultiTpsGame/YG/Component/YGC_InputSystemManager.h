// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "Components/ActorComponent.h"
#include "YGC_InputSystemManager.generated.h"


enum class EYG_InputMappingContext : uint8;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DCIH_MULTITPSGAME_API UYGC_InputSystemManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UYGC_InputSystemManager();

protected:
	virtual void InitializeComponent() override;
	
public:
	UFUNCTION( BlueprintCallable, Category = "Input" )
	void ClearImc();

	UFUNCTION( BlueprintCallable, Category = "Input" )
	void AddImc( EYG_InputMappingContext ImcIndex, int32 Priority, const FModifyContextOptions& Options = FModifyContextOptions() );

	UFUNCTION( BlueprintCallable, Category = "Input" )
	bool RemoveImc( EYG_InputMappingContext ImcIndex, const FModifyContextOptions& Options = FModifyContextOptions() );

	UFUNCTION( BlueprintCallable, Category = "Input" )
	bool HasImc( EYG_InputMappingContext ImcIndex );

	UFUNCTION( BlueprintCallable, Category = "Input" )
	void ChangeInputModeGameOnly( bool bConsumeCaptureMouseDown = true, bool bShowMouseCursor = false );

	UFUNCTION( BlueprintCallable, Category = "Input" )
	void ChangeInputModeUiOnly( UUserWidget* TargetWidget, EMouseLockMode InMouseLockMode = EMouseLockMode::DoNotLock, bool bHideCursorDuringCapture = true );

	UFUNCTION( BlueprintCallable, Category = "Input" )
	UInputMappingContext* GetImc( EYG_InputMappingContext Name );

	UFUNCTION( BlueprintCallable, Category = "Input" )
	UInputAction* GetIa( EYG_InputAction Name );

	void SetPlayer(class APlayerController* NewOwnerPlayer);

protected:
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Input", Meta = (AllowPrivateAccess = "true") )
	TObjectPtr<class UYGDAB_InputDefinition> InputDefinition;

protected:
	UPROPERTY()
	UEnhancedInputComponent* CachedInputComponent;

	UPROPERTY()
	TWeakObjectPtr<class APlayerController> OwnerPlayer;
};
