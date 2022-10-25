// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "GameModeSession.h"

AGameModeSession::AGameModeSession()
{
}

void AGameModeSession::StartPlay()
{
	Super::StartPlay();

	
}

bool AGameModeSession::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	if (CurrentState != EGameModeState::GameOver)
	{
		SetState(EGameModeState::Pause);
	}
	else
	{
		return false;
	}
	
	return Super::SetPause(PC, CanUnpauseDelegate);
}

bool AGameModeSession::ClearPause()
{
	SetState(PreviousState);
	
	return Super::ClearPause();
}

void AGameModeSession::SetState(const EGameModeState& NewState)
{
	if (NewState == CurrentState)
	{
		return;
	}

	PreviousState = CurrentState;
	CurrentState = NewState;
	OnStateChanged.Broadcast(CurrentState);
}
