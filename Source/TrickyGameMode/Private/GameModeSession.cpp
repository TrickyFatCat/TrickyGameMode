// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "GameModeSession.h"

AGameModeSession::AGameModeSession()
{
}

void AGameModeSession::StartPlay()
{
	Super::StartPlay();

	if (PreparationDuration <= 0.f)
	{
		StartSession();
	}
	else if (!IsTimerActive(PreparationTimer))
	{
		SetState(EGameModeState::Preparation);
		GetWorldTimerManager().SetTimer(PreparationTimer, this, &AGameModeSession::StartSession, PreparationDuration);
	}
}

bool AGameModeSession::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	if (CurrentState != EGameModeState::Finished)
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

float AGameModeSession::GetPreparationDuration() const
{
	return PreparationDuration;
}

void AGameModeSession::SetPreparationDuration(const float Value)
{
	PreparationDuration = Value < 0.f ? 0.f : Value;
}

void AGameModeSession::StartSession()
{
	if (!GetWorld())
	{
		return;
	}

	SetState(EGameModeState::InProgress);
}

void AGameModeSession::FinishSession(const bool bIsVictory)
{
	SetState(EGameModeState::Finished);
	OnSessionFinished.Broadcast(bIsVictory);
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

bool AGameModeSession::IsTimerActive(const FTimerHandle& TimerHandle) const
{
	if (!GetWorld())
	{
		return false;
	}

	const FTimerManager& TimerManager = GetWorldTimerManager();

	return TimerManager.IsTimerActive(TimerHandle);
}
