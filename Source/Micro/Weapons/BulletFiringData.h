// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BulletFiringData.generated.h"

class AProjectileBase;

/**
 * 
 */
UCLASS()
class MICRO_API UBulletFiringData : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UBulletFiringData();

	// What projectile class does this weapon fire? If blank, it will default to hitscan.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Bullet Firing Data")
	TSubclassOf<AProjectileBase> ProjectileClass;

	// What is the range of this bullet trace?
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Bullet Firing Data")
	float Range;

	// How much base damage does this bullet do?
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Bullet Firing Data")
	float Damage;

	// Maping for damage multiplier, use this if you want specific bonuses/penalties to apply when a bullet does damage against something. Only applies to hitscan weapons.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Bullet Firing Data")
	TMap<UPhysicalMaterial*, float> DamageMultiplierMap;

	// How many projectiles spawned / hitscans are done in a single trigger pull?
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Bullet Firing Data")
	uint8 ShotsPerTriggerPull;

	// Spread for the bullet. X represents min degrees and Y represent max degrees.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Bullet Firing Data")
	FVector2D SpreadData;

	// What sound is made when the trigger is pulled.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Bullet Firing Data")
	USoundBase* FireSound;
};
