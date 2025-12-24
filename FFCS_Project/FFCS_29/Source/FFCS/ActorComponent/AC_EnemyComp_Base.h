// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FFCS/Asset/FFCS_Data.h"
#include "AC_EnemyComp_Base.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FFCS_API UAC_EnemyComp_Base : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_EnemyComp_Base();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	EAttackHitDirection HitDirection(AActor* Instigator);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetAttackPlayer(bool AttackPlayer);

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, BlueprintCallable)
	bool GetAttackPlayer();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentHealth(const float& Damage);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetPlayerDead(const bool ActorDead);

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, BlueprintCallable)
	float GetCurrentHealth();

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, BlueprintCallable)
	float GetMaxHealth();

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure, BlueprintCallable)
	bool GetPlayerDead();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = true))
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = true))
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = true))
	bool bDead;
	
//protected:
//	// Called when the game starts
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
//
		
};
