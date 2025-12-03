#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JH/Delegates/HealthDelegate.h" // Delegate
#include "HealthComponent.generated.h"

// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSig, float, Current, float, Max);
// 다이나믹 붙으면 조금 더 무거움

UCLASS( )
class DCIH_MULTITPSGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



public:
	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetCurrentHealth() const { return CurHealth; }

	UFUNCTION(BlueprintPure, Category = "Health")
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthRatio() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void ApplyDamage(float damageAmount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(float healAmount);

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnHealthChanged OnHealthChanged;

	UFUNCTION()
	FOnHealthChanged& GetHealthChangedDelegate() { return OnHealthChanged; }
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CurHealth;

private:
	void BroadcastHealth();
};