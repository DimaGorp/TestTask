// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Structs/S_PlayerData.h"
#include "Components/BoxComponent.h" // For UBoxComponent
#include "Components/StaticMeshComponent.h" // For UStaticMeshComponent
#include "Camera/CameraComponent.h" // For UCameraComponent
#include "GameFramework/SpringArmComponent.h" // For USpringArmComponent
#include "FieldPlayer.generated.h"

UCLASS()
class TESTTASK_API AFieldPlayer : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	AFieldPlayer();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;


	//UI events
	//Run in BluePrint

	//Switch Widget based on match state
	UFUNCTION(BlueprintImplementableEvent)
	void UI_MatchState(int index);
	UFUNCTION(BlueprintImplementableEvent)
	void UI_DrawUI();
	UFUNCTION(BlueprintImplementableEvent)
	void PD_SetPlayerProperties(FS_PlayerData Data);
	UFUNCTION(BlueprintImplementableEvent)
	void UI_ChangeScore(int team1_score, int team2_score);
	//Run on owning clients
	//UI Match State
	UFUNCTION(Client, Reliable)
	void C_MatchState(int index);
	UFUNCTION(Client, Reliable)
	void C_ChangeScore(int team1_Score, int team2_Score);
	UFUNCTION(Server, Reliable)
	void S_PlayerSpawned();


	//Movement
	void Move_Sides(float Value);


	//Server Movement Replication
	UFUNCTION(Server, Reliable, WithValidation)
	void S_Move_Sides(float Value);
	// Called to bind functionality to input
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class UFloatingPawnMovement* FloatingPawnMovementComponent;


	// Box collision component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxCollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	// Spring arm for positioning the camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	// Camera to view from
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComponent;
};