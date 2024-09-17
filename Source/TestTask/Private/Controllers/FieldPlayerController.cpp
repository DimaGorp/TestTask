#include "Controllers/FieldPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"   // For Enhanced Input Component
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"
#include "Player/FieldPlayer.h"
#include "GameFramework/Pawn.h"

// Called when the game starts or when spawned
void AFieldPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }
}

// Setup the input component for enhanced input
void AFieldPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Ensure InputComponent is of type UEnhancedInputComponent
    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
    {
        // Bind Move action to the Move function
        if (MoveAction)
        {
            EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFieldPlayerController::Move);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("MoveAction is not assigned in AFieldPlayerController."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to cast InputComponent to UEnhancedInputComponent!"));
    }
}

void AFieldPlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);
    AFieldPlayer* PlayerPawn = Cast<AFieldPlayer>(aPawn);
    PlayerPawn->UI_DrawUI();
    PlayerPawn->S_PlayerSpawned();
}


// Handle movement input
void AFieldPlayerController::Move(const FInputActionValue& Value)
{
    if (!AbbleToMove) {
        return;
    }
    APawn* ControlledPawn = GetPawn();
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (ControlledPawn) {
        AFieldPlayer* PlayerPawn = Cast<AFieldPlayer>(ControlledPawn);
        PlayerPawn->Move_Sides(MovementVector.X);
    }

}


void AFieldPlayerController::MovementState_Implementation(bool Moving)
{
    this->AbbleToMove = Moving;
}