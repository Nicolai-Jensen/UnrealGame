// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UseableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUseableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALGAME_API IUseableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Useable")
	void Use();
};
