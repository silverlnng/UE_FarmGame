// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUserWidget.h"
#include "Components/TextBlock.h"

void UMainUserWidget::SetClock(int32 num)
{
	if(clockText)
	{
		FString IntAsString = FString::FromInt(num);
		FText ftext = FText::FromString(IntAsString);
		clockText->SetText(ftext);
	}
}
