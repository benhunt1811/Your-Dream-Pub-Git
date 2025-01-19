// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "GridSystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PlacableActor.h"
#include "PlayerNumbersComponent.h"
#include "PlayerPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSaved);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGridSystemChanged);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwitchTimeSettings);

UCLASS()
class PUB_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Input action for rotating the camera */
	UPROPERTY(Category = "Input", EditDefaultsOnly)
	UInputAction* RotateCamera;

	/** Input action for zooming the camera */
	UPROPERTY(Category = "Input", EditDefaultsOnly)
	UInputAction* ZoomCamera;

	/** Input action for moving the camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveCamera;

	/** Input action for when placing objects */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Place;

	/** Input actions for rotating the placable object */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RotatePlacableClockwise;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RotatePlacableAntiClockwise;

	/** Input action for resetting the cameras rotation, zoom and position */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ResetCamera;
	
	/** Input action for toggling the grid system when placing */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleGridSys;

	/** Input action for toggling the auto time system */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleAutoTime;

	struct FEnhancedInputActionValueBinding* MoveActionBinding;

	/** Functions for rotating, zooming, moving and resetting camera */
	UFUNCTION(BlueprintCallable)
	void RotateCameraFunction();
	UFUNCTION(BlueprintCallable)
	void ZoomCameraFunction();
	UFUNCTION(BlueprintCallable)
	void MoveCameraFunction(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void ResetCameraFunction(const FInputActionValue& Value);

	/** Functions for placing objects and rotating them */
	UFUNCTION(BlueprintCallable)
	void PlaceObjectFunction(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void RotatePlacableClockwiseFunction(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void RotatePlacableAntiClockwiseFunction(const FInputActionValue& Value);

	/** Function for toggling grid system */
	UFUNCTION(BlueprintCallable)
	void ToggleGridFunction(const FInputActionValue& Value);

	/** Function for toggling auto time system */
	UFUNCTION(BlueprintCallable)
	void ToggleAutoTimeFunction(const FInputActionValue& Value);

	/** Floats for the camera rotation and zoom rates */
	float RotationRate;
	float RotateInputFloat;
	float ZoomInputFloat;

	/** Component for making floating movement for player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	class UFloatingPawnMovement* MyPawnMoveComp;

	/** Function which is used to try place an object, checking if anything is overlapping */
	UFUNCTION(BlueprintCallable)
	void TryPlace(TSubclassOf<APlacableActor> Placable);

	/** Function for resetting mouse location */
	UFUNCTION(BlueprintCallable)
	void ResetMouseLocation();

	/** Storing the actor that needs to be spawned */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placable")
	APlacableActor* SpawnActor;

	/** Boolean to tell if the player is currently trying to place an object */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placable")
	bool Placing;

	/** Function used for calling items use functions */
	UFUNCTION(BlueprintCallable, Category = "Items")
	void UseItem(class UItem* Item);

	/** Creates a player numbers component for player */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UPlayerNumbersComponent* PlayerNumbersComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UGridSystemComponent* GridSystemComponent;

	/** Creates an inventory component for storing current spare items */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UInventoryComponent* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Effects")
	class USoundBase* FinishPlaceSound;

	/** Function for saving a game */
	UFUNCTION(BlueprintCallable)
	void SaveGame();

	/** Function for creating a player save game */
	UFUNCTION(BlueprintCallable)
	void CreateSaveGame();

	/** Function for loading a save game */
	UFUNCTION(BlueprintCallable)
	void LoadGame();

	/** Used to let other scripts know when the game has been saved */
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnSaved OnSaved;

	/** Used to let other scripts know when the grid system has been toggled */
	UPROPERTY(BlueprintAssignable)
	FOnGridSystemChanged GridSystemChanged;

	/** Used to let other scripts know when the auto time system has been toggled */
	UPROPERTY(BlueprintAssignable)
	FOnSwitchTimeSettings SwitchTimeSettings;

	/** Bools used to check when grid system and auto time system are on */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsOnGridPlacing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AutoTime;

	/** Bool used to check if the players done the tutorial, so they only have to see it once */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasDoneTutorial;

	/** Bools used to check if the unlo */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsArea1Unlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsArea2Unlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsArea3Unlocked;
};
