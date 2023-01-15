// Created by Bruce Crum.


#include "Micro/GameFramework/Components/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	HealthValue = 0.0f;
	MaxHealthValue = 150.0f;
	StartingHealthValue = 150.0f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnOwnerTakeDamage);
	SetHealthValue(StartingHealthValue);
}

void UHealthComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// The owner should still be valid, but just in case...
	if (GetOwner())
	{
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::OnOwnerTakeDamage);
	}

	Super::EndPlay(EndPlayReason);
}

void UHealthComponent::ModifyHealth(const float Value)
{
	const float ClampedValue = FMath::Min<float>(HealthValue + Value, MaxHealthValue);
	SetHealthValue(ClampedValue);
}

void UHealthComponent::SetHealthValue(const float NewValue)
{
	HealthValue = NewValue;

	OnHealthUpdatedDelegate.Broadcast(HealthValue, GetHealthRatio());
}

float UHealthComponent::GetHealth() const
{
	return HealthValue;
}

float UHealthComponent::GetHealthRatio() const
{
	const float Divider = MaxHealthValue > FLT_EPSILON ? MaxHealthValue : FLT_EPSILON; // Just to be safe.
	return HealthValue / Divider;
}

void UHealthComponent::OnOwnerTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	ModifyHealth(-Damage);

	if (HealthValue <= 0.0f)
	{
		OnHealthDepletedDelegate.Broadcast(Damage, DamageType, InstigatedBy, DamageCauser);
	}
}