#include "JH/Components/StaminaComponent.h"


UStaminaComponent::UStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxStamina = 100.f;

	CostPerSecond = 10.f;

	RecoverCostPerSecond = 10.f;
	// RecoverDelay = 1.f;
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



void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentStamina = MaxStamina;

	OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);
}


void UStaminaComponent::RecoverPerSecond(float DeltaTime)
{
	CurrentStamina = FMath::Clamp(
		CurrentStamina + RecoverCostPerSecond * DeltaTime,
		0.f, MaxStamina);

	OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);

	//if (CurrentStamina >= MaxStamina)
	//{
	//	GetWorld()->GetTimerManager().ClearTimer(RecoverTimer);
	//}
}



bool UStaminaComponent::CanSprint(float Cost) const
{
	return CurrentStamina >= Cost;
}

void UStaminaComponent::Consume(float Cost)
{
	if (!CanSprint(Cost)) return;

	CurrentStamina = FMath::Clamp(CurrentStamina - Cost, 0.f, MaxStamina);
	OnStaminaChanged.Broadcast(CurrentStamina,MaxStamina);

	GetWorld()->GetTimerManager().ClearTimer(RecoverTimer);

	//GetWorld()->GetTimerManager().SetTimer(
	//	RecoverTimer,
	//	this,
	//	&UStaminaComponent::RecoverPerSecond,
	//	0.2f, true, RecoverDelay
	//);
}

void UStaminaComponent::ConsumePerSecond(float DeltaTime)
{
	CurrentStamina = FMath::Clamp(
		CurrentStamina - CostPerSecond * DeltaTime,
		0.f, MaxStamina
	);

	OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);

	GetWorld()->GetTimerManager().ClearTimer(RecoverTimer);
}

void UStaminaComponent::StartRecover()
{

	//GetWorld()->GetTimerManager().SetTimer(
	//	RecoverTimer,
	//	this,
	//	&UStaminaComponent::RecoverTick,
	//	0.2f, true, RecoverDelay);
}