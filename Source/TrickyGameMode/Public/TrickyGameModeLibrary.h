// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TrickyGameModeLibrary.generated.h"

class AGameModeSession;

/**
 * 
 */
UCLASS()
class TRICKYGAMEMODE_API UTrickyGameModeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="TrickyGameMode", meta=(WorldContext="WorldContextObject"))
	static AGameModeSession* GetSessionGameMode(const UObject* WorldContextObject);
};
