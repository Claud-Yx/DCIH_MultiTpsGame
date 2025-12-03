#pragma once

#include "CoreMinimal.h"
#include "HealthDelegate.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FOnHealthChanged,
    float, Cur,
    float, Max
);
