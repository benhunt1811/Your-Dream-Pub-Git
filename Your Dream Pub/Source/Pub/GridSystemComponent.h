// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "KismetMathLibrary.generated.h"
#include "GridSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PUB_API UGridSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGridSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Size of each grid */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GridSize = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector GridOffset;

	/** Returned vector from the GetGridLocation function */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LocationOnGrid;

	/** Pure function for figuring out an objects location on a grid */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FVector GetGridLocation(FVector Location)
	{
		float XLocation = Location.X;
		float YLocation = Location.Y;

		XLocation -= GridSize / 2;
		YLocation -= GridSize / 2;

		XLocation -= GridOffset.X;
		YLocation -= GridOffset.Y;

		XLocation /= GridSize;
		YLocation /= GridSize;

		XLocation = FMath::RoundToInt(XLocation);
		YLocation = FMath::RoundToInt(YLocation);

		XLocation *= GridSize;
		YLocation *= GridSize;

		XLocation += GridSize / 2;
		YLocation += GridSize / 2;

		LocationOnGrid.X = XLocation;
		LocationOnGrid.Y = YLocation;
		LocationOnGrid.Z = 0;

		LocationOnGrid += GridOffset;

		return LocationOnGrid;
	}

		
};
