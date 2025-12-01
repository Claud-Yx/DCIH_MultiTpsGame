#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthProviderInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnProviderHealthChanged, float, Current, float, Max);

UINTERFACE(MinimalAPI)
class UHealthProviderInterface : public UInterface
{
	GENERATED_BODY()
};

class DCIH_MULTITPSGAME_API IHealthProviderInterface
{
	GENERATED_BODY()

public:
	// UI�� ü�� ���� ��� ���� Getter
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetCurrentHealth();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float GetMaxHealth();

	virtual FOnProviderHealthChanged& GetOnHealthChangedDelegate() = 0;
};
