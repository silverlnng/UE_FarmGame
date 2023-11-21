// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmHUD.h"
#include "MainUserWidget.h"

void AFarmHUD::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World =GetWorld();

	if(World)
	{
		APlayerController* controller =  World->GetFirstPlayerController();	//싱글플레이에서는 오직 1개의 컨트롤러만 있음
		if(controller && MainUserWidgetClass)
		{
			mainUserWidget = CreateWidget<UMainUserWidget>(controller, MainUserWidgetClass);
			mainUserWidget->AddToViewport();
		}
	}
}
