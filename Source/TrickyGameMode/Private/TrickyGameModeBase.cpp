// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "TrickyGameModeBase.h"

DEFINE_LOG_CATEGORY(LogTrickyGameMode);

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
	if (CurrentState == EGameState::Active)
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
