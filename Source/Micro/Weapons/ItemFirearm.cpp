// Created by Bruce Crum.


#include "Micro/Weapons/ItemFirearm.h"
#include "Micro/Weapons/Components/BulletFiringComponent.h"

AItemFirearm::AItemFirearm()
{
	BulletFiring = CreateDefaultSubobject<UBulletFiringComponent>(TEXT("Bullet Firing"));
}
