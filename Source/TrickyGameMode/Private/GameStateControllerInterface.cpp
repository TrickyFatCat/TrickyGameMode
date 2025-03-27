// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "GameStateControllerInterface.h"

bool IGameStateControllerInterface::StartGame_Implementation()
{
	return false;
}

bool IGameStateControllerInterface::FinishGame_Implementation(const EGameResult Result)
{
	return false;
}

bool IGameStateControllerInterface::StopGame_Implementation(const EGameInactivityReason Reason)
{
	return false;
}

bool IGameStateControllerInterface::ChangeInactivityReason_Implementation(const EGameInactivityReason NewInactivityReason)
{
	return false;
}

bool IGameStateControllerInterface::StartPreparation_Implementation()
{
	return false;
}

bool IGameStateControllerInterface::StartCutscene_Implementation()
{
	return false;
}

bool IGameStateControllerInterface::StartTransition_Implementation()
{
	return false;
}

ETrickyGameState IGameStateControllerInterface::GetGameState_Implementation() const
{
	return ETrickyGameState::Inactive;
}

EGameResult IGameStateControllerInterface::GetGameResult_Implementation() const
{
	return  EGameResult::None;
}

EGameInactivityReason IGameStateControllerInterface::GetGameInactivityReason_Implementation() const
{
	return EGameInactivityReason::None;
}

float IGameStateControllerInterface::GetGameElapsedTime_Implementation() const
{
	return -1.f;
}

float IGameStateControllerInterface::GetGameRemainingTime_Implementation() const
{
	return -1.f;
}
