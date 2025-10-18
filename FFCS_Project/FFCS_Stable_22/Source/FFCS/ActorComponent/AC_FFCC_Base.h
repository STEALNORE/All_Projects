// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "FFCS/Asset/FFCS_Data.h"
#include "AC_FFCC_Base.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FFCS_API UAC_FFCC_Base : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_FFCC_Base();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	EAttackHitDirection HitDirection(AActor* Instigator);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayHitMontage(EAttackHitDirection HitDirection);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentEnemy(AActor* EnemyRef);

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, BlueprintCallable)
	AActor* GetCurrentEnemy();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCounterEnemy(AActor* EnemyRef);

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, BlueprintCallable)
	AActor* GetCounterEnemy();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetTag(const FGameplayTag& InTag);

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, BlueprintCallable)
	FGameplayTag GetTag();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Counter")
	void PlayCounterMontage();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Counter")
	void ComboCounter();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Counter")
	void ResetComboCounter();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
	int Counter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timer Handle")
	FTimerHandle ComboCounter_TimerHandle;

//protected:
//	// Called when the game starts
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
