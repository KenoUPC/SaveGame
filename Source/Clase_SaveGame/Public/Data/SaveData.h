#pragma once

#include "CoreMinimal.h"
#include "InventoryItemData.h"
#include "SaveData.generated.h"

// Estructura que agrupa los datos que queremos guardar.
USTRUCT(BlueprintType)
struct FSaveData
{
	GENERATED_BODY()

	// 1. Inventario del jugador.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	TArray<FInventoryItemData> Data;

	// 2. Posición, rotación y escala del personaje.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	FTransform CharacterTransform = FTransform::Identity;
};