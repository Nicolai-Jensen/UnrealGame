// Fill out your copyright notice in the Description page of Project Settings.


#include "CaptureZone.h"

// Sets default values
ACaptureZone::ACaptureZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));

	RootComponent = CollisionComponent;


}

// Called when the game starts or when spawned
void ACaptureZone::BeginPlay()
{
	moneyTaken = false;
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACaptureZone::OnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ACaptureZone::OnOverlapEnd);
	
}

void ACaptureZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	capturing = true;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::White, TEXT("Inside zone"));
		if (moneyTaken == true)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Blue, TEXT("Money already taken! GO!"));
		}

	}

}

void ACaptureZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	capturing = false;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::White, TEXT("Outside zone"));

	}

}

// Called every frame
void ACaptureZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (capturing == true && moneyTaken == false)
	{
		timeSinceTick += DeltaTime;

		percentage = FMath::Clamp(timeSinceTick / CaptureTime * 100.0f, 0.0f, 100.0f);

		displayPercentage = percentage / 100;

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Float value: %f"), displayPercentage));

		if (percentage >= 100.0f)
		{
			capturing = false;

			timeSinceTick = 0;

			GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Blue, TEXT("ALL MONEY COLLECTED!"));

			moneyTaken = true;

		}

	}

}

