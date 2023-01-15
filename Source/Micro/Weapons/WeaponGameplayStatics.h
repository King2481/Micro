// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "WeaponGameplayStatics.generated.h"

class AProjectileBase;

DECLARE_LOG_CATEGORY_EXTERN(LogWeaponGameplayStatics, Log, Verbose);

/**
 * 
 */
UCLASS()
class MICRO_API UWeaponGameplayStatics : public UGameplayStatics
{
	GENERATED_BODY()
	
public:

	// Spawns in a projectile with the specified data
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Weapon Statics")
	static AProjectileBase* FireProjectile(const UObject* WorldContextObject, APawn* Instigator, TSubclassOf<AProjectileBase> ProjectileClass, const FVector& Location, const FVector& ShootDir);
};
