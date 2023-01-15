// Created by Bruce Crum.


#include "Micro/Weapons/BulletFiringData.h"

UBulletFiringData::UBulletFiringData()
{
	ProjectileClass = nullptr;
	Range = 10000.0f;
	Damage = 10.0f;
	ShotsPerTriggerPull = 1;
	SpreadData = FVector2D::ZeroVector;
	FireSound = nullptr;
}