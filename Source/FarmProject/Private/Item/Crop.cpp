// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Crop.h"
#include "MainFarmCharacter.h"

ACrop::ACrop()
{
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	ItemMesh->SetupAttachment(GetRootComponent());
	//ItemMesh->SetCollisionObjectType(ECC_EngineTraceChannel1);
	myType= ECropProgressState::seedState;
}

void ACrop::BeginPlay()
{
	Super::BeginPlay();
	ItemMesh->SetStaticMesh(cropMeshArray[0]);
	
}

void ACrop::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//여기서 enum state에 따라서 mesh를 변경시키기
	
	
}

void ACrop::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//super 으로 부모의 OnSphereOverlap 함수 사용 + 동시에 override으로 재정의
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	/*if(	ItemMesh_2->IsVisible())
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
	}*/
	
}

void ACrop::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	//super 으로 부모의 OnSphereOverlap 함수 사용 + 동시에 override으로 재정의
}




void ACrop::RepeatingGrowingFunction()
{
	
	GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, "timerStart");
	
	if(myType==ECropProgressState::growState)
	{
		GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, "RepeatingGrowingFunction");
		ItemMesh->SetStaticMesh(cropMeshArray[++RepeatingCalls]);
		growingSizeEffect();
	}
	
	GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Black,  FString::FromInt(RepeatingCalls));
	
	if (RepeatingCalls>=RepeatingCallsMax)
	{
		GetWorldTimerManager().ClearTimer(growingTimer);	// growingTimer 은 이제 다른 타이머에 재사용 가능합니다.
		GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Black, "timerEnd");
		RepeatingCalls=0;
		myType= ECropProgressState::cropState;
	}
}

void ACrop::StartTimer()
{
	GetWorldTimerManager().SetTimer(growingTimer,this,&ACrop::RepeatingGrowingFunction,growingRate,true,firstDelay);
}

void ACrop::HighlightActor()
{
	if(myType==ECropProgressState::cropState)
	{
		GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange, "Crop_Highlight");
		ItemMesh->SetRenderCustomDepth(true);
	}
}

void ACrop::UnHighlightActor()
{
	if(myType==ECropProgressState::cropState)
	{
		GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange, "Crop_UnHighlight");
		ItemMesh->SetRenderCustomDepth(false);
	}
}

void ACrop::SetSeedState()
{
	myType=ECropProgressState::seedState;
	ItemMesh->SetStaticMesh(cropMeshArray[0]);
}

//오직 3단계 (ItemMesh_2 가 visible 일때 만 상호작용 가능하도록 만들기)

