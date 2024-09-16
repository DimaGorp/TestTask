// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/PingPongGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Engine/TargetPoint.h"
#include "Player/FieldPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"
#include "Structs/S_PlayerData.h"

APingPongGameMode::APingPongGameMode()
{
    // Set default pawn class using ConstructorHelpers
    static ConstructorHelpers::FClassFinder<APawn> PawnClassFinder(TEXT("/Game/Blueprints/BP_FieldPlayer"));
    DefaultPawnClass = PawnClassFinder.Class;

}
void APingPongGameMode::PostLogin(APlayerController * NewPlayer)
{
    AFieldPlayerController * P_Controller = Cast<AFieldPlayerController>(NewPlayer);
    //P_Controller->MovementState(false);
    int index  = Controllers.Add(P_Controller);
    SpawnPlayer(P_Controller,index);
}

void APingPongGameMode::SpawnPlayer(AFieldPlayerController *Controller, int index)
{
    TArray<AActor*> PlayerStarts;

    // Get all actors of class APlayerStart
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
    FTransform PlayerStartTransform(PlayerStarts[index]->GetActorRotation(),PlayerStarts[index]->GetActorLocation(),FVector(1.0f));

    FActorSpawnParameters parametrs;
    parametrs.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    AFieldPlayer * Pawn = GetWorld()->SpawnActor<AFieldPlayer>(DefaultPawnClass,PlayerStartTransform,parametrs);
    Controller->Possess(Pawn);
}

void APingPongGameMode::PlayerSpawned()
{
    if(!(Controllers.Num() == MaxPlayers)){
        AFieldPlayer * Pawn = Cast<AFieldPlayer>(Controllers[0]->GetPawn());
        Pawn->C_MatchState(3);
        return;
    }
    StartMatch();

}

void APingPongGameMode::StartMatch()
{
    TArray<AActor*> TargetPoints;

    // Get all actors of class APlayerStart
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), TargetPoints);
    FVector PositionOfBall = TargetPoints[0]->GetActorLocation();
    PositionOfBall.Z += 50;

    // Use Quaternion or Rotation directly for FTransform
    FQuat Rotation = TargetPoints[0]->GetActorRotation().Quaternion();  // Get Rotation as Quaternion
    FVector Scale = FVector(1.0f);  // Scale, if needed

    // Create FTransform with Rotation (Quaternion), Translation, and Scale
    FTransform TargetPoint(Rotation, PositionOfBall, Scale);

    for(AFieldPlayerController *Controller : Controllers){
        AFieldPlayer *Player = Cast<AFieldPlayer>(Controller->GetPawn());
        Player->C_MatchState(0);
        Controller->MovementState(true);
    }
    UpdatePlayerScoreUI();
    
}

void APingPongGameMode::UpdatePlayerScoreUI()
{
    for (AFieldPlayerController* Controller : Controllers)
    {
        if (Controller)
        {
            AFieldPlayer* Player = Cast<AFieldPlayer>(Controller->GetPawn());
            if (Player)
            {
                Player->C_ChangeScore(Team1Score, Team2Score);
            }
        }
    }
}

void APingPongGameMode::CheckMatchRule()
{
    if(Team1Score == EndMatchScore){
        PinpongEndMatch(TEXT("Team1"));
    }else if(Team2Score == EndMatchScore)
        PinpongEndMatch(TEXT("Team2"));
}

void APingPongGameMode::OnBallScore(int ScoringTeam)
{
    switch(ScoringTeam){
        case 1:{
            Team1Score++;
            break;
        }
        case 2:{
            Team2Score++;
            break;
        }
    }
    CheckMatchRule();
    UpdatePlayerScoreUI();
}
