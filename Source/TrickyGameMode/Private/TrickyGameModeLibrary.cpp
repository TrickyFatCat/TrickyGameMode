// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "TrickyGameModeLibrary.h"

#include "TrickyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

ATrickyGameModeBase* UTrickyGameModeLibrary::GetTrickyGameMode(const UObject* WorldContextObject)
{
	return Cast<ATrickyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
}

bool UTrickyGameModeLibrary::StartGame(const UObject* WorldContextObject)
{
	if (!ImplementsGameStateInterface(WorldContextObject))
	{
		return false;
	}

	return IGameStateControllerInterface::Execute_StartGame(UGameplayStatics::GetGameMode(WorldContextObject));
}

bool UTrickyGameModeLibrary::StopGame(const UObject* WorldContextObject, const EGameInactivityReason Reason)
{
	if (!ImplementsGameStateInterface(WorldContextObject))
	{
		return false;
	}

	return IGameStateControllerInterface::Execute_StopGame(UGameplayStatics::GetGameMode(WorldContextObject), Reason);
}

bool UTrickyGameModeLibrary::FinishGame(const UObject* WorldContextObject, const EGameResult Result)
{
	if (!ImplementsGameStateInterface(WorldContextObject))
	{
		return false;
	}

	return IGameStateControllerInterface::Execute_FinishGame(UGameplayStatics::GetGameMode(WorldContextObject), Result);
}

bool UTrickyGameModeLibrary::ChangeInactivityReason(const UObject* WorldContextObject, EGameInactivityReason Reason)
{
	if (!ImplementsGameStateInterface(WorldContextObject))
	{
		return false;
	}

	return IGameStateControllerInterface::Execute_ChangeInactivityReason(
		UGameplayStatics::GetGameMode(WorldContextObject), Reason);
}

bool UTrickyGameModeLibrary::StartPreparation(const UObject* WorldContextObject)
{
	if (!ImplementsGameStateInterface(WorldContextObject))
	{
		return false;
	}

	return IGameStateControllerInterface::Execute_StartPreparation(UGameplayStatics::GetGameMode(WorldContextObject));
}

bool UTrickyGameModeLibrary::StartCutscene(const UObject* WorldContextObject)
{
	if (!ImplementsGameStateInterface(WorldContextObject))
	{
		return false;
	}

	return IGameStateControllerInterface::Execute_StartCutscene(UGameplayStatics::GetGameMode(WorldContextObject));
}

bool UTrickyGameModeLibrary::StartTransition(const UObject* WorldContextObject)
{
	if (!ImplementsGameStateInterface(WorldContextObject))
	{
		return false;
	}

	return IGameStateControllerInterface::Execute_StartTransition(UGameplayStatics::GetGameMode(WorldContextObject));
}

ETrickyGameState UTrickyGameModeLibrary::GetGameState(const UObject* WorldContextObject)
{
	if (!ImplementsGameStateInterface(WorldContextObject))
	{
		return ETrickyGameState::Inactive;
	}

	return IGameStateControllerInterface::Execute_GetGameState(UGameplayStatics::GetGameMode(WorldContextObject));
}

EGameResult UTrickyGameModeLibrary::GetGameResult(const UObject* WorldContextObject)
{
	if (!ImplementsGameStateInterface(WorldContextObject))
	{
		return EGameResult::None;
	}

	return IGameStateControllerInterface::Execute_GetGameResult(UGameplayStatics::GetGameMode(WorldContextObject));
}

EGameInactivityReason UTrickyGameModeLibrary::GetInactivityReason(const UObject* WorldContextObject)
{
	if (!ImplementsGameStateInterface(WorldContextObject))
	{
		return EGameInactivityReason::None;
	}

	return IGameStateControllerInterface::Execute_GetGameInactivityReason(
		UGameplayStatics::GetGameMode(WorldContextObject));
}

float UTrickyGameModeLibrary::GetGameElapsedTime(const UObject* WorldContextObject)
{
	if (!ImplementsGameStateInterface(WorldContextObject))
	{
		return -1.f;
	}

	return IGameStateControllerInterface::Execute_GetGameElapsedTime(UGameplayStatics::GetGameMode(WorldContextObject));
}

float UTrickyGameModeLibrary::GetGameRemainingTime(const UObject* WorldContextObject)
{
	if (!ImplementsGameStateInterface(WorldContextObject))
	{
		return -1.f;
	}

	return IGameStateControllerInterface::Execute_GetGameRemainingTime(
		UGameplayStatics::GetGameMode(WorldContextObject));
}

float UTrickyGameModeLibrary::GetGamePreparationRemainingTime(const UObject* WorldContextObject)
{
	const ATrickyGameModeBase* GameMode = GetTrickyGameMode(WorldContextObject);
	const UWorld* World = GameMode->GetWorld();

	if (!IsValid(GameMode) || !IsValid(World))
	{
		return -1.f;
	}

	return World->GetTimerManager().GetTimerRemaining(GameMode->GetPreparationTimerHandle());
}

float UTrickyGameModeLibrary::GetGamePreparationElapsedTime(const UObject* WorldContextObject)
{
	const ATrickyGameModeBase* GameMode = GetTrickyGameMode(WorldContextObject);
	const UWorld* World = GameMode->GetWorld();

	if (!IsValid(GameMode) || !IsValid(World))
	{
		return -1.f;
	}

	return World->GetTimerManager().GetTimerElapsed(GameMode->GetPreparationTimerHandle());
}

bool UTrickyGameModeLibrary::ImplementsGameStateInterface(const UObject* WorldContextObject)
{
	const AGameModeBase* GameMode = UGameplayStatics::GetGameMode(WorldContextObject);

	return GameMode->Implements<UGameStateControllerInterface>();
}
