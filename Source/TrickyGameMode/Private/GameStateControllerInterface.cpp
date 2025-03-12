// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "GameStateControllerInterface.h"


bool IGameStateControllerInterface::BeginGame_Implementation()
{
	return false;
}

bool IGameStateControllerInterface::FinishGame_Implementation(const EGameResult Result)
{
	return false;
}

bool IGameStateControllerInterface::StopGame(const EGameInactivityReason Reason)
{
	return false;
}

bool IGameStateControllerInterface::StopGame_Implementation(const EGameInactivityReason Reason)
{
	return false;
}

bool IGameStateControllerInterface::PauseGame_Implementation()
{
	return false;
}

bool IGameStateControllerInterface::UnpauseGame_Implementation()
{
	return false;
}
