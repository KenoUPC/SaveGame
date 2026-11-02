// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Public/Data/SaveData.h"
#include "DataSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CLASE_SAVEGAME_API UDataSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	// 1. Estructura con todos los datos persistentes.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame)
	FSaveData SavedData;
};
