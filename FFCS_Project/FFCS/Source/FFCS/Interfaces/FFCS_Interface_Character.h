// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FFCS_Interface_Character.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFFCS_Interface_Character : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FFCS_API IFFCS_Interface_Character
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Stun)
	void ApplyStunEffect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Stun)
	void RestartStun();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Stun)
	void EnemyFinalBlow(UAnimMontage* AnimToPlay);
};
