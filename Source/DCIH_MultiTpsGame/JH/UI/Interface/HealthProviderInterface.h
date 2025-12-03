#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "JH/Delegates/HealthDelegate.h" // Delegate

#include "HealthProviderInterface.generated.h"

// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnProviderHealthChanged, float, Current, float, Max);

UINTERFACE(MinimalAPI)
class UHealthProviderInterface : public UInterface
{
	GENERATED_BODY()
};

class DCIH_MULTITPSGAME_API IHealthProviderInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetCurrentHealth();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetMaxHealth();

	// virtual FOnProviderHealthChanged& GetOnHealthChangedDelegate() = 0;

	// HealthComponent의 델리게이트를 그대로 넘겨줌
	virtual FOnHealthChanged& GetHealthChangedDelegate() = 0;
};