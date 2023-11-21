// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmMainGameMode.h"
#include "FarmHUD.h"
#include "MainUserWidget.h"


AFarmMainGameMode::AFarmMainGameMode()
{
	
}

void AFarmMainGameMode::BeginPlay()
{
	Super::BeginPlay();


	AFarmHUD* FarmHUD = Cast<AFarmHUD>(HUDClass);

	if (FarmHUD)
	{
		mainWidget = FarmHUD->GetMainUserWidget();
	}
}
		


void AFarmMainGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	currentTime += DeltaSeconds;
	if (mainWidget)
	{
		mainWidget->SetClock(currentTime);
	}
	
}

