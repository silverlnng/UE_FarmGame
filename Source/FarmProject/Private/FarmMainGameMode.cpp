// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmMainGameMode.h"
#include "UI/FarmHUD.h"
#include "UI/MainUserWidget.h"


AFarmMainGameMode::AFarmMainGameMode()
{
	currentTime = 0;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AFarmMainGameMode::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* controller =  GetWorld()->GetFirstPlayerController();
	if (controller)
	{
		FarmHUD = Cast<AFarmHUD>(controller->GetHUD());
		if (FarmHUD)
		{
			mainWidget = FarmHUD->GetMainUserWidget();
			
		}	
	}
}
		


void AFarmMainGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	currentTime += DeltaSeconds;
	//UE_LOG(LogTemp, Warning, TEXT("%f"), currentTime);
	if (mainWidget)
	{
		mainWidget->SetClockText(currentTime);
	}
	
}

