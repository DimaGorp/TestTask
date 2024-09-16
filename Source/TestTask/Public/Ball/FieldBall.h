#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FieldBall.generated.h"

UCLASS()
class TESTTASK_API ABall : public AActor
{
    GENERATED_BODY()

public:
    // Constructor
    ABall();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Handle the hit event
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);	
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    // Static Mesh for the ball
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UStaticMeshComponent* BallMesh;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    FVector Ball_Velocity;

};