// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TrickyGameModeLibrary.generated.h"

enum class EGameState : uint8;
enum class EGameResult : uint8;
enum class EGameInactivityReason : uint8;
class ATrickyGameModeBase;
/**
 * 
 */
UCLASS()
class TRICKYGAMEMODE_API UTrickyGameModeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static ATrickyGameModeBase* GetTrickyGameMode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static bool StartGame(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static bool StopGame(const UObject* WorldContextObject, EGameInactivityReason Reason);

	UFUNCTION(BlueprintCallable, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static bool FinishGame(const UObject* WorldContextObject, EGameResult Result);

	UFUNCTION(BlueprintCallable, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static bool ChangeInactivityReason(const UObject* WorldContextObject, EGameInactivityReason Reason);

	UFUNCTION(BlueprintCallable, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static bool StartPreparation(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static bool StartCutscene(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static bool StartTransition(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static EGameState GetGameState(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static EGameResult GetGameResult(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static EGameInactivityReason GetInactivityReason(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static float GetGameElapsedTime(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static float GetGameRemainingTime(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static float GetGamePreparationRemainingTime(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static float GetGamePreparationElapsedTime(const UObject* WorldContextObject);
	
private:
	UFUNCTION()
	static bool ImplementsGameStateInterface(const UObject* WorldContextObject);
};



