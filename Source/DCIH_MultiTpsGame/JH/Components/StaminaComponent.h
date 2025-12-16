// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JH/UI/Interface/StaminaUIInterface.h"
#include "StaminaComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DCIH_MULTITPSGAME_API UStaminaComponent 
	: public UActorComponent
	, public IStaminaUIInterface

{
	GENERATED_BODY()

public:	
	UStaminaComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina")
	float MaxStamina = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stamina")
	float CurrentStamina;

	UPROPERTY(EditAnywhere, Category="Stamina")
	float RecoverRate = 5.f;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float RecoverDelay = 1.f;

	UPROPERTY()
	FOnStaminaChanged OnStaminaChanged;

	FTimerHandle RecoverTimer;

	void RecoverTick();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual float GetCurrentStamina_Implementation() const override;
	virtual float GetMaxStamina_Implementation() const override;
	virtual FOnStaminaChanged& GetStaminaChangedDelegate() override;
	

	UFUNCTION(BlueprintCallable)
	bool CanUse(float Cost) const;

	UFUNCTION(BlueprintCallable)
	void Consume(float Cost);

};
