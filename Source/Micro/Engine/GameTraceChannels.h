// Created by Bruce Crum

#pragma once

#include "CoreMinimal.h"
#include "CoreTypes.h"

// Custom collision channels
// This should match DefaultEngine.ini's DefaultChannelResponses definitions
#define ECC_Bullet ECollisionChannel::ECC_GameTraceChannel1
#define ECC_Grab ECollisionChannel::ECC_GameTraceChannel2