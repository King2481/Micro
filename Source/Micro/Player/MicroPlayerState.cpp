// Created by Bruce Crum.


#include "Micro/Player/MicroPlayerState.h"

AMicroPlayerState::AMicroPlayerState()
{

}

void AMicroPlayerState::ModifyScore(float ModifyScoreBy /* = 1.0f*/)
{
	SetScore(GetScore() + ModifyScoreBy);
	OnScoreUpdatedDelegate.Broadcast(FMath::FloorToInt(Score)); // I am not sure why score is a float in Unreal, but we shall just FloorToInt it.
}

void AMicroPlayerState::ResetScore()
{
	SetScore(0);
	OnScoreUpdatedDelegate.Broadcast(0);
}