// Created by Bruce Crum.


#include "Micro/Weapons/WeaponGameplayStatics.h"
#include "Micro/Weapons/Projectiles/ProjectileBase.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY(LogWeaponGameplayStatics);

AProjectileBase* UWeaponGameplayStatics::FireProjectile(const UObject* WorldContextObject, APawn* Instigator, TSubclassOf<AProjectileBase> ProjectileClass, const FVector& Location, const FVector& ShootDir)
{
	UWorld* World = WorldContextObject ? WorldContextObject->GetWorld() : nullptr;
	if (!World)
	{
		UE_LOG(LogWeaponGameplayStatics, Error, TEXT("Error: UWeaponGameplayStatics::FireProjectile() failed (Invalid World)"));
	}

	if (!ProjectileClass)
	{
		UE_LOG(LogWeaponGameplayStatics, Error, TEXT("Error: UWeaponGameplayStatics::FireProjectile() failed (Projectile Class Invalid)"));
		return nullptr;
	}

	if (!World)
	{
		UE_LOG(LogWeaponGameplayStatics, Error, TEXT("Error: UWeaponGameplayStatics::FireProjectile(), failed to fire projectile %s (World is nullptr)"), *ProjectileClass->GetName());
		return nullptr;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Instigator;
	SpawnParams.Owner = Instigator;

	const FTransform SpawnTransform = FTransform(ShootDir.Rotation(), Location);

	AProjectileBase* Projectile = World->SpawnActor<AProjectileBase>(ProjectileClass, SpawnTransform, SpawnParams);
	if (Projectile)
	{
		return Projectile;
	}

	UE_LOG(LogWeaponGameplayStatics, Error, TEXT("Error: UWeaponGameplayStatics::FireProjectile(), failed to fire projectile %s (Failed to spawn)"), *ProjectileClass->GetName());
	return nullptr;
}
