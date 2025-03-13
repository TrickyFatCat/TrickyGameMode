// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "TrickyGameModeBase.h"

void ATrickyGameModeBase::StartPlay()
{
	Super::StartPlay();

	OnGameStopped.Broadcast(InitialInactivityReason);
}

bool ATrickyGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	if (Super::SetPause(PC, CanUnpauseDelegate))
	{
		PauseGame();
		return true;
	}

	return false;
}

bool ATrickyGameModeBase::ClearPause()
{
	if (Super::ClearPause())
	{
		UnpauseGame();
		return true;
	}

	return false;
}

void ATrickyGameModeBase::SetInitialInactivityReason(const EGameInactivityReason Value)
{
	if (InitialInactivityReason == Value)
	{
		return;
	}

	InitialInactivityReason = Value;
}

bool ATrickyGameModeBase::StartGame_Implementation()
{
	if (CurrentState != EGameState::Inactive)
	{
		return false;
	}

	CurrentState = EGameState::Active;
	OnGameStarted.Broadcast();
	return true;
}

bool ATrickyGameModeBase::FinishGame_Implementation(const EGameResult Result)
{
	if (CurrentState != EGameState::Active)
	{
		return false;
	}

	CurrentState = EGameState::Finished;
	OnGameFinished.Broadcast(Result);
	return true;
}

bool ATrickyGameModeBase::StopGame_Implementation(const EGameInactivityReason Reason)
{
	if (CurrentState != EGameState::Active)
	{
		return false;
	}

	CurrentState = EGameState::Inactive;
	OnGameStopped.Broadcast(Reason);
	return true;
}

bool ATrickyGameModeBase::PauseGame_Implementation()
{
	if (CurrentState == EGameState::Paused)
	{
		return false;
	}

	LastState = CurrentState;
	CurrentState = EGameState::Paused;
	OnGamePaused.Broadcast();
	return true;
}

bool ATrickyGameModeBase::UnpauseGame_Implementation()
{
	if (CurrentState != EGameState::Paused)
	{
		return false;
	}
	
	CurrentState = LastState;
	OnGameUnpaused.Broadcast();
	return true;
}
