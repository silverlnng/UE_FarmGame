// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FarmHUD.h"
#include "UI/MainUserWidget.h"

void AFarmHUD::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFarmHUD::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	UWorld* World =GetWorld();

	if(World)
	{
		APlayerController* controller =  World->GetFirstPlayerController();	//�̱��÷��̿����� ���� 1���� ��Ʈ�ѷ��� ����
		if(controller && MainUserWidgetClass)
		{
			mainUserWidget = CreateWidget<UMainUserWidget>(controller, MainUserWidgetClass);
			mainUserWidget->AddToViewport();
		}
	}
}
