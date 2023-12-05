// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/NPC.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>
#include "UI/ItemShopWidget.h"
#include "MainFarmCharacter.h"
// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	cameraComp =CreateDefaultSubobject<UCameraComponent>(TEXT("ZoomCamera"));
	cameraComp->SetupAttachment(RootComponent);
	triggerBox =CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	triggerBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	triggerBox->OnComponentBeginOverlap.AddDynamic(this,&ANPC::OverlapBeginTB);
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::OverlapBeginTB(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OhterComp, int32 OthterBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, OtherActor->GetName());
	
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this,0);
	AMainFarmCharacter* PlayerController=Cast<AMainFarmCharacter>(OtherActor);
	if( PlayerController)
	{
		if (WidgetRef)
		{
			itemShopWidget= CreateWidget<UItemShopWidget>(GetWorld(), WidgetRef);
			itemShopWidget->ownerNPC = this;
			if(itemShopWidget)itemShopWidget->AddToViewport();
		}
		MyPlayerController->SetViewTargetWithBlend(this,1.f);
		//MyPlayerController->SetInputMode(FInputModeUIOnly());
		MyPlayerController->SetShowMouseCursor(true);
	}
}
