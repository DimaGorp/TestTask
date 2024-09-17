#include "Ball/FieldBall.h"
#include "Player/FieldPlayer.h"
#include "Math/UnrealMathUtility.h"
ABall::ABall()
{
    PrimaryActorTick.bCanEverTick = true;
    // Create the static mesh component
    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    RootComponent = BallMesh;
    BallMesh->SetSimulatePhysics(true);
    BallMesh->SetEnableGravity(true);
    FBodyInstance* BodyInstance = BallMesh->GetBodyInstance();
    if (BodyInstance)
    {
        BodyInstance->bLockXTranslation = false; // Lock or limit translations for the X axis
        BodyInstance->bLockYTranslation = false; // Lock or limit translations for the Y axis
        BodyInstance->bLockZTranslation = true; // Lock or limit translations for the Z axis
}
    BallMesh->OnComponentHit.AddDynamic(this, &ABall::OnHit);
}
void ABall::BeginPlay()
{
    std::srand(time(nullptr));
    float Direction = 1;
    if(std::rand()%1){
        Direction = -1;
    }
    this->Ball_Velocity.X = this->Ball_Velocity.Y = Direction;
    this->Ball_Velocity.Z = 0;
    this->Ball_Velocity*=1000;
    BallMesh->AddImpulse(this->Ball_Velocity,NAME_None,true);
}
void ABall::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit)
{
    float Direction = -10.0f;
    if(AFieldPlayer * Player = Cast<AFieldPlayer>(OtherActor)){
        if(BallMesh->GetComponentVelocity().X >1.0f){
            Direction = 10.0f;
        }
        BallMesh->AddImpulse(FVector(Direction,Direction,0.0f));
    }
}
void ABall::Tick(float DeltaTime)
{
}