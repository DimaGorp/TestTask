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
	void SpawnPlayer(AFieldPlayerController* Controller, int index);
	void PlayerSpawned();
	void StartMatch();
	void UpdatePlayerScoreUI();
	void CheckMatchRule();
	UFUNCTION(BlueprintCallable)
	void OnBallScore(int ScoringTeam);
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnBall(FTransform Location);
	UFUNCTION(BlueprintImplementableEvent)
	void DestroyBall();
	void PinpongEndMatch(const FString& Team);
protected:
	TArray<AFieldPlayerController*> Controllers;
	int MaxPlayers=2;
	int EndMatchScore=10;
	int Team1Score=0;
	int Team2Score=0;
};