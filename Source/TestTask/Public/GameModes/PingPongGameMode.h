// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Controllers/FieldPlayerController.h"
#include "PingPongGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASK_API APingPongGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	APingPongGameMode();
	virtual void PostLogin(APlayerController* NewPlayer) override;
	void SpawnPlayer(AFieldPlayerController * Controller,int index);
	void PlayerSpawned();
	void StartMatch();
	void UpdatePlayerScoreUI();
	void CheckMatchRule();
	void OnBallScore(int ScoringTeam);

	UFUNCTION(BlueprintImplementableEvent)
	void GrandPlayersTag();
	UFUNCTION(BlueprintImplementableEvent)
	void PinpongEndMatch(const FString& Team);
protected:
	
	TArray<AFieldPlayerController*> Controllers;
	int MaxPlayers;
	int EndMatchScore;
	int Team1Score;
	int Team2Score;
};
