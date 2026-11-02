#pragma once

#include "CoreMinimal.h"
#include "InventoryItemData.generated.h"

// Estructura que representa un objeto del inventario.
USTRUCT(BlueprintType)
struct FInventoryItemData
{
	GENERATED_BODY()

	// 1. Identificador del objeto.
	// Ejemplo: Wood, Stone, Potion.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	FName ItemID = NAME_None;

	// 2. Cantidad que tenemos de ese objeto.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	int32 Quantity = 0;
};