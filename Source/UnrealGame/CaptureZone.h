// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CaptureZone.generated.h"

UCLASS()
class UNREALGAME_API ACaptureZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACaptureZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)

	UBoxComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CaptureTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float displayPercentage;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	float timeSinceTick;
	float percentage;
	bool capturing;
	bool moneyTaken;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
