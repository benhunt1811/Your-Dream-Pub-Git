// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlacableActor.h"
#include "Item.h"
#include "PubSaveGame.generated.h"

/** Struct used for storing a placable actor and its location when loading them into the game */
USTRUCT(BlueprintType)
struct FAttributes : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class TSubclassOf<APlacableActor> Placable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform PlacableTransform;

	FAttributes()
	{
		Placable = nullptr;
		PlacableTransform = FTransform();
	}

};



UCLASS()
class PUB_API UPubSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPubSaveGame();

	/** Floats used to store money related values */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
	float SaveMoneyValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
	float SaveTotalMoneyValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
	float SaveTotalMoneySpent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
	float SaveNPCMoneyAmount;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	int SaveCapacityValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	int SaveEntertainmentValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	int SaveStyleValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
	int SaveCurrentLevel;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XP")
	int SaveCurrentXP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XP")
	int SaveTotalXP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XP")
	int SaveMaxXP;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	int SaveTotalItemsBought;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	int SaveTotalItemsPlaced;

	UPROPERTY(EditAnywhere, Category = "Items")
	TMap<class TSubclassOf<APlacableActor>, FVector > SavedPlacableItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	FAttributes PlayerSavedPlacables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TArray <FAttributes> PlacableStructArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
	TArray<class UItem*> SavedItemsArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
	TArray<FString> SavedItemsNames;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	FString SavedPubName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	bool HasDoneTutorial;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unlockables")
	bool SaveIsArea1Unlocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unlockables")
	bool SaveIsArea2Unlocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unlockables")
	bool SaveIsArea3Unlocked;
	
};
