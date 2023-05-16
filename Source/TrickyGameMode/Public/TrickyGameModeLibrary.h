// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TrickyGameModeLibrary.generated.h"

class ATrickyGameModeBase;

/**
 * TrickyGameMode helpers library
 */
UCLASS()
class TRICKYGAMEMODE_API UTrickyGameModeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="TrickyGameMode", meta=(WorldContext="WorldContextObject"))
	static ATrickyGameModeBase* GetTrickyGameMode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="TrickyGameMode", meta=(DefaultToSelf="Target", WorldContext="Target"))
	static bool TogglePause(const UObject* Target);
};
