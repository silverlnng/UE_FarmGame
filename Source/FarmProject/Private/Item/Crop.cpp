// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Crop.h"
#include "MainFarmCharacter.h"

ACrop::ACrop()
{
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	ItemMesh->SetupAttachment(GetRootComponent());
	ItemMesh_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent_1"));
	ItemMesh_1->SetupAttachment(GetRootComponent());
	ItemMesh_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent_2"));
	ItemMesh_2->SetupAttachment(GetRootComponent());
}

void ACrop::BeginPlay()
{
	Super::BeginPlay();
	ItemMesh->SetVisibility(true);
	ItemMesh_1->SetVisibility(false);
	ItemMesh_2->SetVisibility(false);
	//생성되자마자 타이머 시작
	GetWorldTimerManager().SetTimer(growingTimer,this,&ACrop::RepeatingGrowingFunction,growingRate,true,firstDelay);
}

void ACrop::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACrop::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//super 으로 부모의 OnSphereOverlap 함수 사용 + 동시에 override으로 재정의
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if(	ItemMesh_2->IsVisible())
	{
		AMainFarmCharacter* mainFarmCharacter = Cast<AMainFarmCharacter>(OtherActor);
		if(mainFarmCharacter)
		{
			GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Yellow, "crop");
			//오직한번만 발생하도록
			ItemMesh_2->ToggleVisibility();
			ItemMesh->ToggleVisibility();
			GetWorldTimerManager().SetTimer(growingTimer,this,&ACrop::RepeatingGrowingFunction,growingRate,true,firstDelay);
		}
	}
	
}

void ACrop::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	//super 으로 부모의 OnSphereOverlap 함수 사용 + 동시에 override으로 재정의
}

void ACrop::RepeatingGrowingFunction()
{
	//켜져있는 0번은 끄고 , 꺼져있는 1번은 키기
	//켜져있는 1번은 끄고 , 꺼져있는 2번은 키기
	GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, "timerStart");
	UStaticMeshComponent* temp=Cast<UStaticMeshComponent>(GetRootComponent()->GetChildComponent(RepeatingCalls));
	UStaticMeshComponent* temp_plus=Cast<UStaticMeshComponent>(GetRootComponent()->GetChildComponent(++RepeatingCalls));
	if(temp)
	{
		GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, temp->GetName());
		temp->ToggleVisibility();
	}
	if(temp_plus)
	{
		GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Purple, temp_plus->GetName());
		temp_plus->ToggleVisibility();
	}
	
	GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Black,  FString::FromInt(RepeatingCalls));
	
	if (RepeatingCalls>=RepeatingCallsMax)
	{
		GetWorldTimerManager().ClearTimer(growingTimer);	// growingTimer 은 이제 다른 타이머에 재사용 가능합니다.
		GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Black, "timerEnd");
		RepeatingCalls=0;
	}
}

//오직 3단계 (ItemMesh_2 가 visible 일때 만 상호작용 가능하도록 만들기)

