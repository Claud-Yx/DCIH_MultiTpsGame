#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "StatUpdatable.generated.h"

UINTERFACE(MinimalAPI)
class UStatUpdatable : public UInterface
{
	GENERATED_BODY()
};

class DCIH_MULTITPSGAME_API IStatUpdatable
{
	GENERATED_BODY()

public:
	virtual class UHealthComponent* GetHealthComponent() = 0;

	virtual void HealthUpdate(float CurrentHealth, float MaxHealth) = 0;
};
