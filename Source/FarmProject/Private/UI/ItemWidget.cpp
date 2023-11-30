// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemWidget.h"
#include "Kismet/DataTableFunctionLibrary.h"

void UItemWidget::GetDataTableRowNames(FName rowID)
{
	FTableRowBase outRow;
	bool RowFound = UDataTableFunctionLibrary::GetDataTableRowFromName(itemDataTable,rowID,outRow);
	if(RowFound)
	{
		//itemDetail = outRow;
		//둘다 struct ,  FTableRowBase을 내가만든 struct에 대입???
	}
}
