// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "StaminaUIInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChanged, float, Cur, float, Max);

UINTERFACE(MinimalAPI)
class UStaminaUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DCIH_MULTITPSGAME_API IStaminaUIInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	float GetCurrentStamina() const;

	UFUNCTION(BlueprintNativeEvent)
	float GetMaxStamina() const;

	virtual FOnStaminaChanged& GetStaminaChangedDelegate() = 0;
};
