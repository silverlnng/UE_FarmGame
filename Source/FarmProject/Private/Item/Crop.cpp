// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Crop.h"

void ACrop::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	//super 으로 부모의 OnSphereOverlap 함수 사용 + 동시에 override으로 재정의
	
}

void ACrop::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	//super 으로 부모의 OnSphereOverlap 함수 사용 + 동시에 override으로 재정의
}
