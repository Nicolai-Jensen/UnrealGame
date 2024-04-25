// Fill out your copyright notice in the Description page of Project Settings.


#include "MyVaultDoor2.h"

// Sets default values
AMyVaultDoor2::AMyVaultDoor2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));


	RootComponent = CollisionComponent;
	DoorMesh->SetupAttachment(RootComponent);

	doorState = EVaultState::CLOSED;
}

// Called when the game starts or when spawned
void AMyVaultDoor2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyVaultDoor2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (opening)
	{
		timeSinceTick += DeltaTime;

		percentage = FMath::Clamp(timeSinceTick / OpenTime * 100.0f, 0.0f, 100.0f);

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Float value: %f"), percentage));

		float newRotation;

		if (doorState == EVaultState::CLOSED)
		{
			newRotation = FMath::Lerp(0.0f, 90.0f, percentage / 100.0f);
		}
		else if (doorState == EVaultState::OPENED)
		{
			newRotation = FMath::Lerp(90.0f, 0.0f, percentage / 100.0f);
		}



		FRotator newLocation = DoorMesh->GetRelativeRotation();

		newLocation.Yaw = newRotation;

		DoorMesh->SetRelativeRotation(newLocation);

		if (percentage >= 100.0f)
		{
			opening = false;
			timeSinceTick = 0;

			doorState = (doorState == EVaultState::CLOSED) ? EVaultState::OPENED : EVaultState::CLOSED;
		}
	}

}

void AMyVaultDoor2::Use_Implementation()
{
	opening = true;
}

