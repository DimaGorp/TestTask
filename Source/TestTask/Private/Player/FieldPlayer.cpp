// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FieldPlayer.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
AFieldPlayer::AFieldPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	FloatingPawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovementComponent"));
    if (FloatingPawnMovementComponent)
    {
        FloatingPawnMovementComponent->UpdatedComponent = RootComponent;
        FloatingPawnMovementComponent->MaxSpeed = 600.0f;
        FloatingPawnMovementComponent->Acceleration = 4000.0f;
        FloatingPawnMovementComponent->Deceleration = 800.0f;
    }
    // Ensure replication is enabled
    bReplicates = true;
}

// Called when the game starts or when spawned
void AFieldPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFieldPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AFieldPlayer::C_ChangeScore_Implementation(int team1_Score,int team2_Score){
	UI_ChangeScore(team1_Score,team2_Score);
}
void AFieldPlayer::C_MatchState_Implementation(int index)
{
	UI_MatchState(index);
}
void AFieldPlayer::Move_Sides(float Value)

{
	Value*=10;
	if(HasAuthority()){
		FVector DesiredLocation = GetActorLocation();
		DesiredLocation.Y += Value;
		SetActorLocation(FMath::VInterpTo(GetActorLocation(),DesiredLocation,GetWorld()->GetDeltaSeconds(),5.0f),true); 
	}else{
		S_Move_Sides(Value);
	}
}

void AFieldPlayer::S_Move_Sides_Implementation(float Value)
{
    Move_Sides(Value);
}

bool AFieldPlayer::S_Move_Sides_Validate(float Value)
{
    return true;
}
// Called to bind functionality to input
void AFieldPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFieldPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AFieldPlayer, PlayerData);
}

void AFieldPlayer::OnRep_S_PlayerData()
{
    PD_SetPlayerProperties(PlayerData);
}