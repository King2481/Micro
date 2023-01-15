// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "BulletFiringComponent.generated.h"

class UBulletFiringData;
class UNiagaraSystem;
class UNiagaraComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogBulletFiring, Log, Verbose);

USTRUCT(BlueprintType)
struct FStoredFirearmHit
{
	GENERATED_BODY()

	// The actor that we had hit.
	UPROPERTY()
	AActor* HitActor;

	// The physical material that we hit.
	UPROPERTY()
	TWeakObjectPtr<UPhysicalMaterial> PhysMaterial;

	// Origin of the shot
	UPROPERTY()
	FVector_NetQuantize Origin;

	// Where the shot landed
	UPROPERTY()
	FVector_NetQuantize ImpactPoint;

	// The impact normal of the hit
	UPROPERTY()
	FVector_NetQuantizeNormal ImpactNormal;

	// The direction of the shot
	UPROPERTY()
	FVector_NetQuantize ShotDirection;

	FStoredFirearmHit()
	{
		HitActor = nullptr;
		PhysMaterial = nullptr;
		Origin = FVector_NetQuantize();
		ImpactPoint = FVector_NetQuantize();
		ImpactNormal = FVector_NetQuantize();
		ShotDirection = FVector_NetQuantize();
	}

	FStoredFirearmHit(AActor* StoredActor, TWeakObjectPtr<UPhysicalMaterial> StoredMaterial, const FVector& StoredOrigin, const FVector& StoredImpactPoint, const FVector& StoredImpactNormal, const FVector& StoredShotDirection)
	{
		HitActor = StoredActor;
		PhysMaterial = StoredMaterial;
		Origin = StoredOrigin;
		ImpactPoint = StoredImpactPoint;
		ImpactNormal = StoredImpactNormal;
		ShotDirection = StoredShotDirection;
	}
};

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MICRO_API UBulletFiringComponent : public UArrowComponent
{
	GENERATED_BODY()
	
public:

	UBulletFiringComponent();

	// Pulls the trigger and fires a shot.
	UFUNCTION(BlueprintCallable, Category = "Bullet Firing Component")
	void OnPullTrigger();

	// Releases the trigger and stops all firing logic (if any).
	UFUNCTION(BlueprintCallable, Category = "Bullet Firing Component")
	void OnReleaseTrigger();

protected:

	// What BulletFiringData is used to determine hitscan characteristics.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Bullet Firing Component")
	UBulletFiringData* BulletFiringData;

private:

	// The actual weapon trace for hitscan based bullets.
	FHitResult WeaponTrace(const FVector& StartTrace, const FVector& EndTrace) const;

	// Calculates damage from the shot based on what was hit.
	float CalculateDamageFromShot(const FStoredFirearmHit& Hit) const;

	// Fires a bullet based on the components BulletFiringData, which can either be hitscan or projectile.
	void FireBullet();

	// Processes any hitscan hits we had.
	void ProcessInstantHits(const TArray<FStoredFirearmHit>& Hits);
};
