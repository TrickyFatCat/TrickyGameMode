﻿// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "TrickyGameModeBase.h"

DEFINE_LOG_CATEGORY(LogTrickyGameMode);

void ATrickyGameModeBase::StartPlay()
{
	Super::StartPlay();

	CurrentInactivityReason = InitialInactivityReason;
	OnGameStopped.Broadcast(CurrentInactivityReason);

	if (CurrentInactivityReason == EGameInactivityReason::Preparation && PreparationDuration > 0.0f)
	{
		StartPreparationTimer();
	}
}

bool ATrickyGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	if (Super::SetPause(PC, CanUnpauseDelegate))
	{
		PauseGame();

		if (LastState == EGameState::Inactive && CurrentInactivityReason == EGameInactivityReason::Preparation)
		{
			PausePreparationTimer();
		}
		
		return true;
	}

	return false;
}

bool ATrickyGameModeBase::ClearPause()
{
	if (Super::ClearPause())
	{
		UnpauseGame();

		if (CurrentState == EGameState::Inactive && CurrentInactivityReason == EGameInactivityReason::Preparation)
		{
			UnPausePreparationTimer();
		}
		return true;
	}

	return false;
}

void ATrickyGameModeBase::SetPreparationDuration(const float Value)
{
	if (Value < 0.0f)
	{
		return;
	}

	PreparationDuration = Value;
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
	if (CurrentState == EGameState::Active || CurrentState == EGameState::Paused)
	{
		return false;
	}

	CurrentState = EGameState::Active;
	Execute_ChangeInactivityReason(this, EGameInactivityReason::None);
	OnGameStarted.Broadcast();

#if WITH_EDITOR || !UE_BUILD_SHIPPING
	PrintLog("Game Started");
#endif

	return true;
}

bool ATrickyGameModeBase::FinishGame_Implementation(const EGameResult Result)
{
	if (CurrentState != EGameState::Active)
	{
		return false;
	}

	CurrentState = EGameState::Finished;
	GameResult = Result;
	OnGameFinished.Broadcast(Result);

#if WITH_EDITOR || !UE_BUILD_SHIPPING
	FString ResultName = "NONE";
	GetGameResultName(ResultName, Result);
	PrintLog(FString::Printf(TEXT("Game Finished with Result: %s"), *ResultName));
#endif

	return true;
}

bool ATrickyGameModeBase::StopGame_Implementation(const EGameInactivityReason Reason)
{
	if (CurrentState != EGameState::Active)
	{
		return false;
	}

	CurrentState = EGameState::Inactive;
	Execute_ChangeInactivityReason(this, Reason);
	OnGameStopped.Broadcast(Reason);

#if WITH_EDITOR || !UE_BUILD_SHIPPING
	FString ReasonName = "NONE";
	GetInactivityReasonName(ReasonName, Reason);
	PrintLog(FString::Printf(TEXT("Game Stopped with Reason: %s"), *ReasonName));
#endif
	return true;
}

bool ATrickyGameModeBase::StartPreparation_Implementation()
{
	if (CurrentState != EGameState::Inactive)
	{
		return StopGame(EGameInactivityReason::Preparation);
	}

	return Execute_ChangeInactivityReason(this, EGameInactivityReason::Preparation);
}

bool ATrickyGameModeBase::StartCutscene_Implementation()
{
	if (CurrentState != EGameState::Inactive)
	{
		return StopGame(EGameInactivityReason::Cutscene);
	}

	return Execute_ChangeInactivityReason(this, EGameInactivityReason::Cutscene);
}

bool ATrickyGameModeBase::StartTransition_Implementation()
{
	if (CurrentState != EGameState::Inactive)
	{
		return StopGame(EGameInactivityReason::Transition);
	}

	return Execute_ChangeInactivityReason(this, EGameInactivityReason::Transition);
}

EGameResult ATrickyGameModeBase::GetGameResult_Implementation() const
{
	if (CurrentState != EGameState::Finished)
	{
		return EGameResult::None;
	}

	return GameResult;
}

bool ATrickyGameModeBase::PauseGame_Implementation()
{
	if (CurrentState == EGameState::Paused || CurrentState == EGameState::Finished)
	{
		return false;
	}

	LastState = CurrentState;
	CurrentState = EGameState::Paused;
	OnGamePaused.Broadcast();

#if WITH_EDITOR || !UE_BUILD_SHIPPING
	PrintLog("Game Paused");
#endif

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

#if WITH_EDITOR || !UE_BUILD_SHIPPING
	FString StateName = "NONE";
	GetGameStateName(StateName, CurrentState);
	PrintLog(FString::Printf(TEXT("Game Unpaused. Current State: %s"), *StateName));
#endif

	return true;
}

bool ATrickyGameModeBase::ChangeInactivityReason_Implementation(const EGameInactivityReason NewInactivityReason)
{
	if (CurrentInactivityReason == NewInactivityReason)
	{
		return false;
	}

	CurrentInactivityReason = NewInactivityReason;
	OnInactivityReasonChanged.Broadcast(CurrentInactivityReason);

#if WITH_EDITOR || !UE_BUILD_SHIPPING
	FString ReasonName = "NONE";
	GetInactivityReasonName(ReasonName, CurrentInactivityReason);
	PrintLog(FString::Printf(TEXT("Inactivity Reason changed to: %s"), *ReasonName));
#endif

	return true;
}

bool ATrickyGameModeBase::StartPreparationTimer()
{
	const UWorld* World = GetWorld();

	if (!IsValid(World) || !World->IsGameWorld())
	{
		return false;
	}

	FTimerManager& TimerManager = World->GetTimerManager();

	if (!PreparationTimerHandle.IsValid() || TimerManager.IsTimerActive(PreparationTimerHandle))
	{
		return false;
	}

	TimerManager.SetTimer(PreparationTimerHandle,
	                      this,
	                      &ATrickyGameModeBase::HandlePreparationTimerFinished,
	                      PreparationDuration,
	                      false);

#if WITH_EDITOR || !UE_BUILD_SHIPPING
	PrintLog(FString::Printf(TEXT("Preparation Timer started. Duration: %.2f"), PreparationDuration));
#endif
	return true;
}

void ATrickyGameModeBase::HandlePreparationTimerFinished()
{
	StartGame();
}

bool ATrickyGameModeBase::StopPreparationTimer()
{
	const UWorld* World = GetWorld();

	if (!IsValid(World) || !World->IsGameWorld())
	{
		return false;
	}

	FTimerManager& TimerManager = World->GetTimerManager();

	if (!PreparationTimerHandle.IsValid() || !TimerManager.IsTimerActive(PreparationTimerHandle))
	{
		return false;
	}

	TimerManager.ClearTimer(PreparationTimerHandle);

#if WITH_EDITOR || !UE_BUILD_SHIPPING
	PrintLog("Preparation Timer stopped");
#endif
	
	return true;
}

bool ATrickyGameModeBase::PausePreparationTimer()
{
	const UWorld* World = GetWorld();

	if (!IsValid(World) || !World->IsGameWorld())
	{
		return false;
	}

	FTimerManager& TimerManager = World->GetTimerManager();

	if (!PreparationTimerHandle.IsValid() || !TimerManager.IsTimerActive(PreparationTimerHandle))
	{
		return false;
	}

	TimerManager.PauseTimer(PreparationTimerHandle);

#if WITH_EDITOR || !UE_BUILD_SHIPPING
	const float RemainingTime = TimerManager.GetTimerRemaining(PreparationTimerHandle);
	const FString LogMessage = FString::Printf(TEXT("Preparation Timer paused. Time: %.2f"), RemainingTime);
	PrintLog(LogMessage);
#endif
	
	return true;
}

bool ATrickyGameModeBase::UnPausePreparationTimer()
{	const UWorld* World = GetWorld();
 
 	if (!IsValid(World) || !World->IsGameWorld())
 	{
 		return false;
 	}
 
 	FTimerManager& TimerManager = World->GetTimerManager();
 
 	if (!PreparationTimerHandle.IsValid() || TimerManager.IsTimerActive(PreparationTimerHandle))
 	{
 		return false;
 	}
 
 	TimerManager.UnPauseTimer(PreparationTimerHandle);

#if WITH_EDITOR || !UE_BUILD_SHIPPING
	const float RemainingTime = TimerManager.GetTimerRemaining(PreparationTimerHandle);
	const FString LogMessage = FString::Printf(TEXT("Preparation Timer un-paused. Time: %.2f"), RemainingTime);
	PrintLog(LogMessage);
#endif
	
 	return true;
}

#if WITH_EDITOR || !UE_BUILD_SHIPPING
void ATrickyGameModeBase::PrintWarning(const FString& Message) const
{
	UE_LOG(LogTrickyGameMode, Warning, TEXT("%s"), *Message);
}

void ATrickyGameModeBase::PrintLog(const FString& Message) const
{
	UE_LOG(LogTrickyGameMode, Display, TEXT("%s"), *Message);
}

void ATrickyGameModeBase::GetGameStateName(FString& StateName, const EGameState State)
{
	StateName = StaticEnum<EGameState>()->GetNameStringByValue(static_cast<int64>(State));
}

void ATrickyGameModeBase::GetInactivityReasonName(FString& ReasonName, const EGameInactivityReason Reason)
{
	ReasonName = StaticEnum<EGameInactivityReason>()->GetNameStringByValue(static_cast<int64>(Reason));
}

void ATrickyGameModeBase::GetGameResultName(FString& ResultName, const EGameResult Result)
{
	ResultName = StaticEnum<EGameResult>()->GetNameStringByValue(static_cast<int64>(Result));
}
#endif
