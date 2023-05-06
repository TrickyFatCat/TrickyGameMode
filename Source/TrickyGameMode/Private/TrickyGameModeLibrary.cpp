// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "TrickyGameModeLibrary.h"

#include "TrickyGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ATrickyGameModeBase* UTrickyGameModeLibrary::GetSessionGameMode(const UObject* WorldContextObject)
{
	return Cast<ATrickyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
}
