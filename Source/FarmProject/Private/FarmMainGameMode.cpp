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
	APlayerController* controller =  GetWorld()->GetFirstPlayerController();
	FarmHUD = Cast<AFarmHUD>(controller->GetHUD());
	mainWidget = FarmHUD->GetMainUserWidget();
	mainWidget->SetClock(1);
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

