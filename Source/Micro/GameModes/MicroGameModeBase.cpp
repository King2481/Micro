// Copyright Epic Games, Inc. All Rights Reserved.


#include "MicroGameModeBase.h"
#include "Micro/Player/MicroPlayerState.h"

AMicroGameModeBase::AMicroGameModeBase()
{
	PlayerStateClass = AMicroPlayerState::StaticClass();
}