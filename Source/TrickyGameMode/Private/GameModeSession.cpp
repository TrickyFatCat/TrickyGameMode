// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "GameModeSession.h"
#include "TimerManager.h"
#include "Engine/World.h"

AGameModeSession::AGameModeSession()
{
}

void AGameModeSession::StartPlay()
{
	Super::StartPlay();

	if (bManualStart)
	{
		OnStateChanged.Broadcast(EGameModeState::Inactive);
		return;
	}

	if (PreparationDuration <= 0.f)
	{
		StartSession();
	}
	else if (!IsTimerActive(PreparationTimer))
	{
		StartPreparation();
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

void AGameModeSession::StartSession()
{
	if (!GetWorld())
	{
		return;
	}

	SetState(EGameModeState::InProgress);

	if (bLimitSessionTime && !IsTimerActive(SessionTimer))
	{
		FTimerDelegate SessionTimerDelegate;
		SessionTimerDelegate.BindUFunction(this, "FinishSession", bVictoryOnTimeOver);
		GetWorldTimerManager().SetTimer(SessionTimer, SessionTimerDelegate, SessionDuration, false);
	}
	else
	{
		TimeOnStart = GetWorld()->GetTimeSeconds();
	}
}

void AGameModeSession::FinishSession(const bool bIsVictory)
{
	SetState(EGameModeState::Finished);

	FinalTime = bLimitSessionTime ? GetSessionRemainingTime() : GetSessionElapsedTime();

	if (bLimitSessionTime && IsTimerActive(SessionTimer))
	{
		GetWorldTimerManager().ClearTimer(SessionTimer);
	}

	OnSessionFinished.Broadcast(bIsVictory, FinalTime);
}

void AGameModeSession::StartPreparation()
{
	SetState(EGameModeState::Preparation);
	GetWorldTimerManager().SetTimer(PreparationTimer, this, &AGameModeSession::StartSession, PreparationDuration);
}

float AGameModeSession::GetSessionElapsedTime() const
{
	if (!GetWorld())
	{
		return -1.f;
	}

	return bLimitSessionTime
		       ? GetWorldTimerManager().GetTimerElapsed(SessionTimer)
		       : GetWorld()->GetTimeSeconds() - TimeOnStart;
}

float AGameModeSession::GetSessionRemainingTime() const
{
	if (!GetWorld())
	{
		return -1.f;
	}

	return bLimitSessionTime ? GetWorldTimerManager().GetTimerRemaining(SessionTimer) : GetSessionElapsedTime();
}

bool AGameModeSession::IsManualStart() const
{
	return bManualStart;
}

void AGameModeSession::SetState(const EGameModeState NewState)
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
