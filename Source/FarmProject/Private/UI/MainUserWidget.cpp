// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUserWidget.h"
#include "Components/TextBlock.h"

void UMainUserWidget::SetClockText(float num)
{
	if(clockText)
	{
		int32 IntNumb = FMath::FloorToInt(num);
		IntNumb=IntNumb*24;
		
		int32 day = IntNumb / (24 * 3600);
		//FString dayString = FString::FromInt(day);
		//FText daytext = FText::FromString(dayString);
		
		IntNumb = IntNumb % (24 * 3600); 
		int32 hour = IntNumb / 3600; 
		//FString hourString = FString::FromInt(hour);
		//FText hourtext = FText::FromString(hourString);
		
		IntNumb %= 3600; 
		int32 minutes = IntNumb / 60 ;
		//FString minuteString = FString::FromInt(minutes);
		//FText minutetext = FText::FromString(minuteString);
		
		//FString IntAsString = FString::FromInt(IntNumb);

		//FString timerString = FString::Printf(TEXT("[%s] ÀÏ,[%s] :,[%s]"),*dayString ,*hourString ,*minuteString);
		
		FText timerText = FText::Format(FText::FromString("{0}DAY  {1}Hour  {2}Min"),day ,hour ,minutes);
		
		//FText ftext = FText::FromString(timerText);
		
		clockText->SetText(timerText);
	}
}
