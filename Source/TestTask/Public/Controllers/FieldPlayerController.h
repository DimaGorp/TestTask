// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h" 
#include "FieldPlayerController.generated.h"

/**
 *
 */
UCLASS()
class TESTTASK_API AFieldPlayerController : public APlayerController
{
    GENERATED_BODY()
public:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;
    virtual void OnPossess(APawn* aPawn) override;
    //Bool variable to Enable/Disable Input
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    bool AbbleToMove = true;


    UFUNCTION(Client, Reliable)
    void MovementState(bool Moving);
protected:
    void Move(const FInputActionValue& Value);
    // Input Mapping Context
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    class UInputMappingContext* DefaultMappingContext;
    // Input Actions
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    class UInputAction* MoveAction;

};