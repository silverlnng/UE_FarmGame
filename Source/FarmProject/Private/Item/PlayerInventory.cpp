// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PlayerInventory.h"

// Sets default values for this component's properties
UPlayerInventory::UPlayerInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerInventory::AddItem(FName itemID, int32 quantity)
{
	if(inventoryMap.Find(itemID))
	{
		inventoryMap.Add(itemID,*inventoryMap.Find(itemID)+quantity);
	}
	else
	{
		inventoryMap.Add(itemID,quantity);
	}
}

void UPlayerInventory::RemoveItem(FName itemID, int quantity)
{
	if(inventoryMap.Find(itemID))
	{
		if(*inventoryMap.Find(itemID)-1>0)
		{
			inventoryMap.Add(itemID,*inventoryMap.Find(itemID)-quantity);
		}
		else
		{
			inventoryMap.Remove(itemID);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, "removeItem not found");
	}
}

