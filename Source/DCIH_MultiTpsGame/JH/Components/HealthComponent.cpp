#include "JH/Components/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurHealth = FMath::Clamp(CurHealth, 0.f, MaxHealth);
	BroadcastHealth();
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::ApplyDamage(float DamageAmount)
{
	CurHealth = FMath::Clamp(CurHealth - DamageAmount, 0.f, MaxHealth);
	
	// 체력 변경 브로드캐스팅
	BroadcastHealth();
}

void UHealthComponent::Heal(float HealAmount)
{
	CurHealth = FMath::Clamp(CurHealth + HealAmount, 0.f, MaxHealth);
	// 체력 변경 알림
	BroadcastHealth();
}

float UHealthComponent::GetHealthRatio() const
{
	return (MaxHealth > 0.f) ? (CurHealth / MaxHealth) : 0.f;
}

void UHealthComponent::BroadcastHealth()
{
	UE_LOG(LogTemp, Warning, TEXT(" BroadcastHealth: %f / %f"), CurHealth, MaxHealth);

	OnHealthChanged.Broadcast(CurHealth, MaxHealth);
}
