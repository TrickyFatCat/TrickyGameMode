// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "TrickyGameModeLibrary.h"

#include "GameModeSession.h"
#include "Kismet/GameplayStatics.h"

AGameModeSession* UTrickyGameModeLibrary::GetSessionGameMode(const UObject* WorldContextObject)
{
	return Cast<AGameModeSession>(UGameplayStatics::GetGameMode(WorldContextObject));
}
