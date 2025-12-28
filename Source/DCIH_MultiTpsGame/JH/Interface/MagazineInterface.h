#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "MagazineInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnMagazineChanged,
	int32,
	MagazineNum
);

UINTERFACE(MinimalAPI)
class UMagazineInterface : public UInterface
{
	GENERATED_BODY()
};

class DCIH_MULTITPSGAME_API IMagazineInterface
{
	GENERATED_BODY()

public:
	virtual FOnMagazineChanged& GetMagazineChangedDelegate() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddMagazine();
};