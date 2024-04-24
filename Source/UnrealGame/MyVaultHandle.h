// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "UseableInterface.h"
#include "MyVaultHandle.generated.h"




UENUM(BlueprintType)
enum class EHandleState : uint8
{
	OPENED, CLOSED,
};

UCLASS()
class UNREALGAME_API AMyVaultHandle : public AActor, public IUseableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyVaultHandle();


	UFUNCTION(BlueprintImplementableEvent, Category = "Handle")
	void HandleFullyOpened();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OpenTime;

	float timeSinceTick;

	float percentage;

	bool opening;

	bool hasOpened;

	EHandleState doorState;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Use_Implementation() override;


};
