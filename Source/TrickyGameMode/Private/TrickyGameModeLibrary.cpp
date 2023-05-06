// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "TrickyGameModeLibrary.h"

#include "TrickyGameModeBase.h"
#include "TrickyPlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

ATrickyGameModeBase* UTrickyGameModeLibrary::GetTrickyGameMode(const UObject* WorldContextObject)
{
	return Cast<ATrickyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
}

bool UTrickyGameModeLibrary::TogglePause(const UObject* Target)
{
	return UGameplayStatics::IsGamePaused(Target)
		       ? UGameplayStatics::SetGamePaused(Target, false)
		       : UGameplayStatics::SetGamePaused(Target, true);
}
