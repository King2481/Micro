// Created by Bruce Crum.


#include "Micro/Items/ItemBase.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	ItemMesh->CastShadow = true;
	ItemMesh->bOnlyOwnerSee = false;
	ItemMesh->bOwnerNoSee = true;

	SetRootComponent(ItemMesh);
}

