// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "TrickyGameModeBase.h"
#include "TimerManager.h"
#include "Engine/World.h"

ATrickyGameModeBase::ATrickyGameModeBase()
{
}

void ATrickyGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
#if WITH_EDITORONLY_DATA
	if (bShowDebug)
	{
		const FString Message = FString::Printf(TEXT("%s\nPreparation : %.2f\nGame Time : %.2f"),
			*UEnum::GetValueAsString(CurrentState),
			GetWorldTimerManager().GetTimerRemaining(PreparationTimer),
			GetSessionRemainingTime());
		GEngine->AddOnScreenDebugMessage(0,
		                                 DeltaSeconds,
		                                 FColor::Magenta,
		                                 Message,
		                                 true,
		                                 FVector2D{1.25f, 1.25f});
	}
#endif
}

void ATrickyGameModeBase::StartPlay()
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

bool ATrickyGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	switch (CurrentState)
	{
	case EGameModeState::Win:
	case EGameModeState::Lose:
	case EGameModeState::Transition:
		return false;

	default:
		SetState(EGameModeState::Pause);
		break;
	}

	return Super::SetPause(PC, CanUnpauseDelegate);
}

bool ATrickyGameModeBase::ClearPause()
{
	SetState(PreviousState);

	return Super::ClearPause();
}

void ATrickyGameModeBase::StartSession()
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

void ATrickyGameModeBase::FinishSession(const bool bIsVictory)
{
	SetState(bIsVictory ? EGameModeState::Win : EGameModeState::Lose);

	FinalTime = bLimitSessionTime ? GetSessionRemainingTime() : GetSessionElapsedTime();

	if (bLimitSessionTime && IsTimerActive(SessionTimer))
	{
		GetWorldTimerManager().ClearTimer(SessionTimer);
	}
}

void ATrickyGameModeBase::StartPreparation()
{
	SetState(EGameModeState::Preparation);
	GetWorldTimerManager().SetTimer(PreparationTimer, this, &ATrickyGameModeBase::StartSession, PreparationDuration);
}

float ATrickyGameModeBase::GetSessionElapsedTime() const
{
	if (!GetWorld() || CurrentState == EGameModeState::Preparation)
	{
		return -1.f;
	}

	return bLimitSessionTime
		       ? GetWorldTimerManager().GetTimerElapsed(SessionTimer)
		       : (GetWorld()->GetTimeSeconds() - TimeOnStart);
}

float ATrickyGameModeBase::GetSessionRemainingTime() const
{
	if (!GetWorld() || CurrentState == EGameModeState::Preparation)
	{
		return -1.f;
	}

	return bLimitSessionTime ? GetWorldTimerManager().GetTimerRemaining(SessionTimer) : GetSessionElapsedTime();
}

bool ATrickyGameModeBase::IsManualStart() const
{
	return bManualStart;
}

void ATrickyGameModeBase::SetState(const EGameModeState NewState)
{
	if (NewState == CurrentState)
	{
		return;
	}

	PreviousState = CurrentState;
	CurrentState = NewState;
	OnStateChanged.Broadcast(CurrentState);
}

bool ATrickyGameModeBase::IsTimerActive(const FTimerHandle& TimerHandle) const
{
	if (!GetWorld())
	{
		return false;
	}

	const FTimerManager& TimerManager = GetWorldTimerManager();

	return TimerManager.IsTimerActive(TimerHandle);
}
