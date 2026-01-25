#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "InteractTarget.generated.h"

UINTERFACE(MinimalAPI)
class UInteractTarget : public UInterface
{
	GENERATED_BODY()
};

class DCIH_MULTITPSGAME_API IInteractTarget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInteract(class AActor* Interactor);
};
