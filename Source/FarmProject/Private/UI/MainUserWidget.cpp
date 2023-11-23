// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUserWidget.h"
#include "Components/TextBlock.h"

void UMainUserWidget::SetClockText(float num)
{
	if(clockText)
	{
		int32 IntNumb = FMath::FloorToInt(num);
		
		FString IntAsString = FString::FromInt(IntNumb);
		FText ftext = FText::FromString(IntAsString);
		clockText->SetText(ftext);
	}
}
