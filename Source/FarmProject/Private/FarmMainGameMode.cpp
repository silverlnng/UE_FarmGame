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
	if (controller)
	{
		UE_LOG(LogTemp, Log, TEXT("controller!=null"));
		FarmHUD = Cast<AFarmHUD>(controller->GetHUD());
		if (FarmHUD)
		{
			UE_LOG(LogTemp, Log, TEXT("FarmHUD!=null"));
			UMainUserWidget* mainWidget_ = FarmHUD->mainUserWidget;
			if (mainWidget_)
			{	UE_LOG(LogTemp, Log, TEXT("mainWidget!=null"));
				mainWidget_->SetClock(1);
			}
		}	
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

