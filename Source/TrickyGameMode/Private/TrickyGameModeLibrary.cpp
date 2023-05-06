// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "TrickyGameModeLibrary.h"

#include "TrickyGameModeBase.h"
#include "TrickyPlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

ATrickyGameModeBase* UTrickyGameModeLibrary::GetTrickyGameMode(const UObject* WorldContextObject)
{
	return Cast<ATrickyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
}

bool UTrickyGameModeLibrary::TogglePause(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject))
	{
		return false;
	}

	ATrickyPlayerControllerBase* PlayerController = Cast<ATrickyPlayerControllerBase>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));

	if (!PlayerController)
	{
		return false;
	}

	PlayerController->TogglePause();
	return true;
}

