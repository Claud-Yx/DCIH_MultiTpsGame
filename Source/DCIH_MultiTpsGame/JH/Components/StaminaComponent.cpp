#include "JH/Components/StaminaComponent.h"


UStaminaComponent::UStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentStamina = MaxStamina;
}


void UStaminaComponent::RecoverTick()
{
	CurrentStamina = FMath::Clamp(
		CurrentStamina + RecoverRate,
		0.f, MaxStamina
	);

	OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);

	if (CurrentStamina >= MaxStamina)
	{
		GetWorld()->GetTimerManager().ClearTimer(RecoverTimer);
	}
}

void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

float UStaminaComponent::GetCurrentStamina_Implementation() const
{
	return CurrentStamina;
}

float UStaminaComponent::GetMaxStamina_Implementation() const
{
	return MaxStamina;
}

FOnStaminaChanged& UStaminaComponent::GetStaminaChangedDelegate()
{
	return OnStaminaChanged;
}

bool UStaminaComponent::CanUse(float Cost) const
{
	return CurrentStamina >= Cost;
}

void UStaminaComponent::Consume(float Cost)
{
	if (!CanUse(Cost)) return;

	CurrentStamina = FMath::Clamp(CurrentStamina - Cost, 0.f, MaxStamina);
	OnStaminaChanged.Broadcast(CurrentStamina,MaxStamina);

	GetWorld()->GetTimerManager().ClearTimer(RecoverTimer);
	GetWorld()->GetTimerManager().SetTimer(
		RecoverTimer,
		this,
		&UStaminaComponent::RecoverTick,
		0.2f, true, RecoverDelay
	);
}

