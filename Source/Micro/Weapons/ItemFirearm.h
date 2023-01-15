// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "Micro/Weapons/ItemWeapon.h"
#include "ItemFirearm.generated.h"

class UBulletFiringComponent;

/**
 * 
 */
UCLASS()
class MICRO_API AItemFirearm : public AItemWeapon
{
	GENERATED_BODY()

public:

	AItemFirearm();

protected:

	// The bullet firing component that every firearm has.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Item Firearm")
	UBulletFiringComponent* BulletFiring;

};
