// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthUpdatedDelegate, float, NewHealth, float, AsNormalizedRatio);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthDepletedDelegate, float, Damage, const UDamageType*, DamageType, AController*, InstigatedBy, AActor*, DamageCauser);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MICRO_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	// Modifies the health by the specified value.
	UFUNCTION(BlueprintCallable, Category = "Health Component")
	void ModifyHealth(const float Value);

	// This will set the health component to this value. 
	UFUNCTION(BlueprintCallable, Category = "Health Component")
	void SetHealthValue(const float NewValue);

	// Returns the current health value
	UFUNCTION(BlueprintPure, Category = "Health Component")
	float GetHealth() const;

	// Returns the current health value as a normalized value between 0 and 1, where 0 means no health and 1 means max health.
	UFUNCTION(BlueprintPure, Category = "Health Component")
	float GetHealthRatio() const;

	// Called when the health actually updates.
	UPROPERTY(BlueprintAssignable)
	FOnHealthUpdatedDelegate OnHealthUpdatedDelegate;

	// Called when the health has reached 0
	UPROPERTY(BlueprintAssignable)
	FOnHealthDepletedDelegate OnHealthDepletedDelegate;

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called when the component ends play.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
		
	// What is the currently stored health value on this component?
	UPROPERTY(BlueprintReadOnly, Category = "Health Component")
	float HealthValue;

	// What is the maximum allowed value? If above this, the health component will tick down to this value.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Health Component")
	float MaxHealthValue;

	// When this component is initialized, what is the starting health value?
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Health Component")
	float StartingHealthValue;

	// Called when the owning actors takes damage
	UFUNCTION()
	void OnOwnerTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
