// Created by Bruce Crum.


#include "Micro/Weapons/Components/BulletFiringComponent.h"
#include "Micro/Weapons/BulletFiringData.h"
#include "Micro/Engine/GameTraceChannels.h"
#include "Micro/Weapons/WeaponGameplayStatics.h"
#include "Micro/Weapons/Projectiles/ProjectileBase.h"
#include "Kismet/GameplayStatics.h"

#if !UE_BUILD_SHIPPING
// Debug helpers
#include "Kismet/KismetSystemLibrary.h"

static TAutoConsoleVariable<int32> CvarShowWeaponTraces(TEXT("DebugWeaponTraces"), 0, TEXT("Visualise Firearm Traces"));
#endif

DEFINE_LOG_CATEGORY(LogBulletFiring);

UBulletFiringComponent::UBulletFiringComponent()
{
	BulletFiringData = nullptr;
}

void UBulletFiringComponent::OnPullTrigger()
{
	FireBullet();
}

void UBulletFiringComponent::OnReleaseTrigger()
{

}

void UBulletFiringComponent::FireBullet()
{
	if (BulletFiringData == nullptr)
	{
		return;
	}

	TArray<FStoredFirearmHit> StoredHits;

	// Cache them as local variables as the code is easier to read.
	const FVector ForwardVector = GetForwardVector();
	const FVector StartTrace = GetComponentLocation();
	const FVector2D LocalSpreadData = BulletFiringData->SpreadData;

	for (uint8 i = 0; i < BulletFiringData->ShotsPerTriggerPull; i++)
	{
		FRandomStream WeaponRandomStream(FMath::Rand());
		const float ConeHalfAngle = FMath::DegreesToRadians(FMath::RandRange(LocalSpreadData.X, LocalSpreadData.Y));

		const FVector ShootDir = WeaponRandomStream.VRandCone(ForwardVector, ConeHalfAngle, ConeHalfAngle);
		const FVector EndTrace = StartTrace + (ShootDir * BulletFiringData->Range);

		if (BulletFiringData->ProjectileClass)
		{
			UWeaponGameplayStatics::FireProjectile(this, GetOwner()->GetInstigator(), BulletFiringData->ProjectileClass, StartTrace, ShootDir);
		}
		else
		{
			const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);
			StoredHits.Add(FStoredFirearmHit(Impact.GetActor(), Impact.PhysMaterial, StartTrace, Impact.ImpactPoint, Impact.ImpactNormal, ShootDir));
		}
	}

	if (StoredHits.Num())
	{
		ProcessInstantHits(StoredHits);
	}

	if (BulletFiringData->FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, BulletFiringData->FireSound, GetComponentLocation());
	}
}

void UBulletFiringComponent::ProcessInstantHits(const TArray<FStoredFirearmHit>& Hits)
{
	for (auto& Hit : Hits)
	{
		if (Hit.HitActor)
		{
			if (Hit.HitActor->CanBeDamaged())
			{
				UGameplayStatics::ApplyPointDamage(Hit.HitActor, CalculateDamageFromShot(Hit), GetForwardVector(), FHitResult(), nullptr, GetOwner(), UDamageType::StaticClass());
			}
		}
	}
}

float UBulletFiringComponent::CalculateDamageFromShot(const FStoredFirearmHit& Hit) const
{
	const float BaseDamage = BulletFiringData->Damage;
	float Multiplier = 1.0f;

	if (BulletFiringData)
	{
		if (BulletFiringData->DamageMultiplierMap.Contains(Hit.PhysMaterial.Get()))
		{
			Multiplier *= *BulletFiringData->DamageMultiplierMap.Find(Hit.PhysMaterial.Get());
		}
	}

	return BaseDamage * Multiplier;
}

FHitResult UBulletFiringComponent::WeaponTrace(const FVector& StartTrace, const FVector& EndTrace) const
{
	// Perform trace to retrieve hit info
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	Params.AddIgnoredActor(GetOwner()->GetOwner());
	Params.bTraceComplex = false;
	Params.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Bullet, Params);

#if !UE_BUILD_SHIPPING
	if (CvarShowWeaponTraces.GetValueOnGameThread() > 0)
	{
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), StartTrace, EndTrace, FLinearColor::Red, 1.0f, 1.0f);

		if (Hit.GetActor())
		{
			UKismetSystemLibrary::DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 10.0f, 12, FLinearColor::Yellow, 1.0f, 1.0f);
		}
	}
#endif

	return Hit;
}