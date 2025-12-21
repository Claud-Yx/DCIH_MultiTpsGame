// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JH/UI/Interface/StaminaUIInterface.h"
#include "StaminaComponent.generated.h"

UCLASS( ClassGroup=(StaminaComponent), meta=(BlueprintSpawnableComponent) )
class DCIH_MULTITPSGAME_API UStaminaComponent 

	: public UActorComponent
	, public IStaminaUIInterface

{
	GENERATED_BODY()

public:	
	UStaminaComponent();



	// Interface_StaminaUIInterface
	virtual float GetCurrentStamina_Implementation() const override;
	virtual float GetMaxStamina_Implementation() const override;
	virtual FOnStaminaChanged& GetStaminaChangedDelegate() override;



	UFUNCTION(BlueprintCallable)
	bool CanSprint(float Cost = 0.f) const;

	UFUNCTION(BlueprintCallable)
	void Consume(float Cost);

	UFUNCTION(BlueprintCallable)
	void ConsumePerSecond(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void RecoverPerSecond(float DeltaTime);
	
	UFUNCTION(BlueprintCallable)
	void StartRecover();



protected:
	virtual void BeginPlay() override;







protected:
	UPROPERTY(BlueprintAssignable, Category = "Stamina")
	FOnStaminaChanged OnStaminaChanged;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina")
	float MaxStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina")
	float CurrentStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float CostPerSecond;

	FTimerHandle RecoverTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stamina")
	float RecoverCostPerSecond;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float RecoverDelay;
};
