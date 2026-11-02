// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Core/SaveGameSubsystem.h"

#include "Clase_SaveGameCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Public/SaveGame/DataSaveGame.h"

void USaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USaveGameSubsystem::Deinitialize()
{
	// 1. Liberamos la referencia al objeto SaveGame.
	CurrentSaveGame = nullptr;

	// 2. Finalizamos la clase padre.
	Super::Deinitialize();
	
	// 3. Ejecutamos la finalización de la clase padre.
	Super::Deinitialize();
}
void USaveGameSubsystem::SaveGameData(const FSaveData& Data)
{
	// 1. Comprobamos que no exista otra operación en curso.
	if (bIsBusy)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("SAVE: El sistema está ocupado"));
		return;
	}

	// 2. Marcamos el Subsystem como ocupado.
	bIsBusy = true;

	// 3. Creamos un objeto de nuestra clase SaveGame.
	CurrentSaveGame = Cast<UDataSaveGame>(
		UGameplayStatics::CreateSaveGameObject(
			UDataSaveGame::StaticClass()
		)
	);

	// 4. Comprobamos que el objeto se creó correctamente.
	if (!CurrentSaveGame)
	{
		UE_LOG(LogTemp, Error,
			TEXT("SAVE: No se pudo crear el SaveGame"));

		bIsBusy = false;
		OnSaveCompleted.Broadcast(false);
		return;
	}

	// 5. Copiamos todos los datos recibidos al SaveGame.
	CurrentSaveGame->SavedData = Data;

	// 6. Creamos el delegado nativo del guardado.
	FAsyncSaveGameToSlotDelegate SaveDelegate;

	// 7. Vinculamos el delegado con nuestra función callback.
	SaveDelegate.BindUObject(
		this,
		&USaveGameSubsystem::HandleSaveCompleted
	);

	// 8. Iniciamos el guardado asíncrono.
	UGameplayStatics::AsyncSaveGameToSlot(CurrentSaveGame,SlotName,UserIndex,SaveDelegate);

	// 9. La función termina sin esperar el guardado.
	// El resultado llegará a HandleSaveCompleted().
}

void USaveGameSubsystem::HandleSaveCompleted(
	const FString& SavedSlot,
	const int32 SavedUserIndex,
	bool bSuccess
)
{
	// 1. Marcamos el Subsystem como disponible.
	bIsBusy = false;

	// 2. Comprobamos el resultado del guardado.
	if (bSuccess)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("SAVE: Datos guardados correctamente en %s"),
			*SavedSlot
		);
	}
	else
	{
		UE_LOG(LogTemp, Error,
			TEXT("SAVE: No se pudieron guardar los datos")
		);
	}

	// 3. Liberamos nuestra referencia al SaveGame.
	CurrentSaveGame = nullptr;

	// 4. Notificamos a los sistemas que estén suscritos.
	OnSaveCompleted.Broadcast(bSuccess);
}

void USaveGameSubsystem::LoadGameData()
{
	// 1. Comprobamos que no exista otra operación.
	if (bIsBusy)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("LOAD: El sistema está ocupado"));
		return;
	}

	// 2. Comprobamos que exista el archivo guardado.
	if (!UGameplayStatics::DoesSaveGameExist(
		SlotName,
		UserIndex
	))
	{
		UE_LOG(LogTemp, Warning,
			TEXT("LOAD: No existe una partida guardada"));

		// Notificamos que no se pudo cargar.
		OnLoadCompleted.Broadcast(false, FSaveData());
		return;
	}

	// 3. Marcamos el Subsystem como ocupado.
	bIsBusy = true;

	// 4. Creamos el delegado nativo de carga.
	FAsyncLoadGameFromSlotDelegate LoadDelegate;

	// 5. Vinculamos nuestro callback.
	LoadDelegate.BindUObject(
		this,
		&USaveGameSubsystem::HandleLoadCompleted
	);

	// 6. Iniciamos la carga asíncrona.
	UGameplayStatics::AsyncLoadGameFromSlot(
		SlotName,
		UserIndex,
		LoadDelegate
	);

	// 7. Los datos todavía no están disponibles.
	// Llegarán cuando se ejecute HandleLoadCompleted().
}

void USaveGameSubsystem::HandleLoadCompleted(
	const FString& LoadedSlot,
	const int32 LoadedUserIndex,
	USaveGame* LoadedGame
)
{
	// 1. Marcamos el Subsystem como disponible.
	bIsBusy = false;

	// 2. Convertimos el objeto recibido a nuestra clase.
	UDataSaveGame* Save = Cast<UDataSaveGame>(LoadedGame);

	// 3. Comprobamos que los datos sean válidos.
	if (!Save)
	{
		UE_LOG(LogTemp, Error,
			TEXT("LOAD: No se pudo cargar el SaveGame"));

		OnLoadCompleted.Broadcast(false, FSaveData());
		return;
	}

	// 4. Copiamos la estructura recuperada.
	FSaveData LoadedData = Save->SavedData;

	// 5. Mostramos un mensaje de confirmación.
	UE_LOG(LogTemp, Warning,
		TEXT("LOAD: Datos cargados desde %s"),
		*LoadedSlot
	);

	// 6. Enviamos los datos a los sistemas suscritos.
	OnLoadCompleted.Broadcast(true, LoadedData);
}