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
		UE_LOG(LogTemp, Log, TEXT("controller!=null"));
		FarmHUD = Cast<AFarmHUD>(controller->GetHUD());
		if (FarmHUD)
		{
			UE_LOG(LogTemp, Log, TEXT("FarmHUD!=null"));
			mainWidget = FarmHUD->mainUserWidget;
			if (mainWidget)
			{	UE_LOG(LogTemp, Log, TEXT("mainWidget!=null"));
				//mainWidget->SetClock(1);
			}
		}	
	}
}
		


void AFarmMainGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	currentTime += DeltaSeconds;
	UE_LOG(LogTemp, Warning, TEXT("%f"),currentTime);
	if (mainWidget)
	{
		//UE_LOG(LogTemp, Warning, TEXT("&d"),currentTime);
		int32 IntNumb = FMath::FloorToInt(currentTime);
		mainWidget->SetClock(IntNumb);
	}
	
}

