// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TrickyGameModeLibrary.generated.h"

class ATrickyGameModeBase;

/**
 * 
 */
UCLASS()
class TRICKYGAMEMODE_API UTrickyGameModeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="TrickyGameMode", meta=(WorldContext="WorldContextObject"))
	static ATrickyGameModeBase* GetSessionGameMode(const UObject* WorldContextObject);
};
