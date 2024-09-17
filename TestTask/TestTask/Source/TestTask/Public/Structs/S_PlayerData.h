#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "S_PlayerData.generated.h"

USTRUCT(BlueprintType) // This makes the struct usable in Blueprints
struct FS_PlayerData
{
    GENERATED_BODY() // Necessary for structs to enable reflection and Blueprint functionality

    // Properties

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Info")
    FString Team;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Stats")
    UMaterialInstanceDynamic* Color; // Changed to pointer type
};
