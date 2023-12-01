// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Item/Crop.h"
#include "MainFarmCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


AMainPlayerController::AMainPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	bEnableClickEvents=true;
	
}

void AMainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	//Locomotion();
	CursorTrace();
	//�������� �ִ°�� interp�۵���Ű��
	
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	check(PlayerMappingContext);
	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(subsystem);
	subsystem->AddMappingContext(PlayerMappingContext, 0);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;

	//FInputModeGameAndUI : �Է� ��嵵 ������ �� �ֽ��ϴ�.
	/*���� �Է� ��� ���Ӱ� UI ����ü�� �Է� ��� ����ü�̸�, �� �Է� ��带 ����Ѵٸ�
	Ű����� ���콺�� �Է��� ����� �� ������ �Է��� ����Ͽ� ������ ���� UI�� ������ �� �� �ֽ��ϴ�.*/

	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	mainFarmCharacter = Cast<AMainFarmCharacter>(GetCharacter());
	//controller���忡�� characterã��� getowner �� �ƴ϶� GetCharacter !!
	
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &AMainPlayerController::Move);
	EnhancedInputComponent->BindAction(ClickIA, ETriggerEvent::Started, this, &AMainPlayerController::Clicked);
	
}

void AMainPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector forwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(forwardDirection, InputAxisVector.Y);
		ControllerPawn->AddMovementInput(rightDirection, InputAxisVector.X);
	}
	
}

void AMainPlayerController::Locomotion()
{
	moveDir = FTransform(GetControlRotation()).TransformVector(moveDir);
	if (APawn* ControllerPawn = GetPawn<APawn>())
	{
		ControllerPawn->AddMovementInput(moveDir);		//
	}
    //������ �ʱ�ȭ
    moveDir = FVector::ZeroVector;
}

void AMainPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (!CursorHit.bBlockingHit) return;
	//sGEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange, CursorHit.GetActor()->GetName());
	LastActor = ThisActor;
	ThisActor = Cast<ACrop>(CursorHit.GetActor());
	
	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case B
			ThisActor->HighlightActor();
			GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange,"this !=null");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange,"this,last both null");
			// Case A - both are null, do nothing
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnHighlightActor();
		}
		else // both actors are valid
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case E - do nothing
			}
		}
	}
}

void AMainPlayerController::Clicked()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	
	ACrop* crop = Cast<ACrop>(HitResult.GetActor());
	if(crop)
	{
		if(crop->myType==ECropProgressState::growState)
		{
			if(mainFarmCharacter)
			{
			 GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange,"crop 0 state Clicked");
			/*mainFarmCharacter->GetCharacterMovement()
			->MoveSmooth(crop->GetActorLocation().GetSafeNormal(),5);*/
				FVector temp = crop->GetActorLocation()-mainFarmCharacter->GetActorLocation();
				mainFarmCharacter->GetCharacterMovement()
				->MoveSmooth(temp,5);
				
				//�÷��̾��� ��� �ִϸ��̼� ��Ÿ�� �۵���Ű��
				mainFarmCharacter->ChangedAnimMontage(1);
				//crop�� grow Ÿ�̸� �۵���Ű��
				//
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange,"mainFarmCharacter ==null");
			}
		}
		
		if(crop->myType==ECropProgressState::cropState)
		{
			GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Orange,"ECropProgressState::cropState");
			FVector temp = crop->GetActorLocation()-mainFarmCharacter->GetActorLocation();
			mainFarmCharacter->GetCharacterMovement()
			->MoveSmooth(temp,5);
			//mainFarmCharacter->GetCharacterMovement()->Move
			//�÷��̾��� ��Ȯ �ִϸ��̼� ��Ÿ�� �۵���Ű��
			//ECropProgressState::growState ���� �����Ű��
			//�κ��丮�� �ֱ�
		}
	}
	
	if (HitResult.GetComponent())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Mouse Click+++ Component: %s"), *HitResult.GetComponent()->GetName()) );
	}

	if (HitResult.GetActor())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Mouse Click+++ Actor: %s"), *HitResult.GetActor()->GetName()));
	}
}

