// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveGameSubsystem.generated.h"

struct FSaveData;
class USaveGame;
class AClase_SaveGameCharacter;
class UDataSaveGame;

// 1. Delegado que informa el resultado del guardado.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveCompleted,bool,bSuccess);

// 2. Delegado que informa el resultado de la carga.
// Devuelve también la estructura FSaveData.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLoadCompleted,bool, bSuccess,FSaveData, LoadedData);
/**
 * 
 */
UCLASS()
class CLASE_SAVEGAME_API USaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	// 3. Inicialización automática del Subsystem.
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// 4. Finalización automática del Subsystem.
	virtual void Deinitialize() override;

	// 5. Inicia el guardado asíncrono.
	UFUNCTION(BlueprintCallable, Category="SaveGame")
	void SaveGameData(const FSaveData& Data);

	// 6. Inicia la carga asíncrona.
	UFUNCTION(BlueprintCallable, Category="SaveGame")
	void LoadGameData();

	// 7. Evento que se emite cuando finaliza el guardado.
	UPROPERTY(BlueprintAssignable, Category="SaveGame")
	FOnSaveCompleted OnSaveCompleted;

	// 8. Evento que se emite cuando finaliza la carga.
	UPROPERTY(BlueprintAssignable, Category="SaveGame")
	FOnLoadCompleted OnLoadCompleted;

private:

	// 9. Nombre del slot utilizado para guardar.
	const FString SlotName = TEXT("PlayerSave");

	// 10. Índice del usuario local.
	const int32 UserIndex = 0;

	// 11. Mantiene una referencia al SaveGame durante
	// la operación de guardado.
	UPROPERTY()
	TObjectPtr<UDataSaveGame> CurrentSaveGame = nullptr;

	// 12. Evita operaciones simultáneas.
	bool bIsBusy = false;

	// 13. Callback nativo del guardado asíncrono.
	void HandleSaveCompleted(const FString& SavedSlot, const int32 SavedUserIndex,bool bSuccess);

	// 14. Callback nativo de la carga asíncrona.
	void HandleLoadCompleted(const FString& LoadedSlot, const int32 LoadedUserIndex,USaveGame* LoadedGame);
};
