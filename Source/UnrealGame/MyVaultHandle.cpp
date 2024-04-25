// Fill out your copyright notice in the Description page of Project Settings.


#include "MyVaultHandle.h"

// Sets default values
AMyVaultHandle::AMyVaultHandle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Handle"));


	RootComponent = CollisionComponent;
	DoorMesh->SetupAttachment(RootComponent);

	doorState = EHandleState::CLOSED;
	hasOpened = false;
}

// Called when the game starts or when spawned
void AMyVaultHandle::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AMyVaultHandle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (hasOpened == false)
	{
		if (opening)
		{
			timeSinceTick += DeltaTime;

			percentage = FMath::Clamp(timeSinceTick / OpenTime * 100.0f, 0.0f, 100.0f);

			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Float value: %f"), percentage));

			float newRotation;

			if (doorState == EHandleState::CLOSED)
			{
				newRotation = FMath::Lerp(0.0f, -360.0f, percentage / 100.0f);
			}

			FRotator newLocation = DoorMesh->GetRelativeRotation();

			newLocation.Pitch = newRotation;

			DoorMesh->SetRelativeRotation(newLocation);

			if (percentage >= 100.0f)
			{
				opening = false;
				timeSinceTick = 0;

				doorState = (doorState == EHandleState::CLOSED) ? EHandleState::OPENED : EHandleState::CLOSED;
				hasOpened = true;

				HandleFullyOpened();
			}
		}

	}
}


void AMyVaultHandle::Use_Implementation()
{
	opening = true;
}


