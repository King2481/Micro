// Created by Bruce Crum.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MicroPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreUpdatedDelegate, int32, NewScore);

/**
 * 
 */
UCLASS()
class MICRO_API AMicroPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	AMicroPlayerState();
	
	// Delegate for when the score get's updated. (So the UI doesn't have to check every frame)
	UPROPERTY(BlueprintAssignable)
	FOnScoreUpdatedDelegate OnScoreUpdatedDelegate;

	// Modifies the score by a specified amount (Note, this is not a setter, but more of an adder/subtractor)
	UFUNCTION(BlueprintCallable, Category = "Micro Player State")
	void ModifyScore(float ModifyScoreBy = 1.0f);

	// Resets the score back to 0.
	UFUNCTION(BlueprintCallable, Category = "Micro Player State")
	void ResetScore();
};
