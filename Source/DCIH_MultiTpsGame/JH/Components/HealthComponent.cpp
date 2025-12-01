#include "JH/Components/HealthComponent.h"
#include "JH/Character/JHCharacter.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.f;
	CurHealth = 100.f;
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
	
	// ü�� ���� ��ε�ĳ����
	BroadcastHealth();
}

void UHealthComponent::Heal(float HealAmount)
{
	CurHealth = FMath::Clamp(CurHealth + HealAmount, 0.f, MaxHealth);
	// ü�� ���� �˸�
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
