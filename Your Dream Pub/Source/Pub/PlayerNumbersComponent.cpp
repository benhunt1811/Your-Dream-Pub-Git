// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerNumbersComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlacableActor.h"
#include "NPC.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UPlayerNumbersComponent::UPlayerNumbersComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	LevelUpSound = CreateDefaultSubobject<USoundBase>(TEXT("LevelUpSound"));

	CountMax = 5;
}


// Called when the game starts
void UPlayerNumbersComponent::BeginPlay()
{
	Super::BeginPlay();

	UpdateNPCMoneyAmount();

	// ...
	
}


// Called every frame
void UPlayerNumbersComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentXP >= MaxXP)
	{
		IncreaseLevel();
	}

	Count += DeltaTime;

	if (Count >= CountMax)
	{
		TArray<AActor*> NPCs;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPC::StaticClass(), NPCs);

		OnScreenMoneyValue += NPCMoneyAmount * NPCs.Num();
		Count = 0;

		APlayerPawn* Player = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (Player)
		{
			Player->SaveGame();
		}

		OnNPCUpdated.Broadcast();
	}
}

void UPlayerNumbersComponent::IncreaseLevel()
{
	CurrentLevel++;
	CurrentXP -= MaxXP;
	MaxXP += 10;

	UpdateNPCMoneyAmount();

	OnLevelUp.Broadcast();


	if (LevelUpSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), LevelUpSound, 1, 1, 0, NULL, NULL, true);
	}
}

void UPlayerNumbersComponent::UpdateNPCMoneyAmount()
{
	float Money = (CurrentLevel + StyleLevel++ + EntertainmentLevel++) * 2;

	NPCMoneyAmount = FMath::RoundUpToPowerOfTwo(Money);
}

