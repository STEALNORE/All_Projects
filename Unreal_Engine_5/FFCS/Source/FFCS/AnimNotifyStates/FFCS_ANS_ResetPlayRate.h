// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "FFCS_ANS_ResetPlayRate.generated.h"

/**
 * 
 */
UCLASS()
class FFCS_API UFFCS_ANS_ResetPlayRate : public UAnimNotifyState
{
	GENERATED_BODY()

	UFFCS_ANS_ResetPlayRate();
	
public:
	//Used For Debugging Distance And Playrate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Config")
	bool Debug;
	
	//Max Range of Distance the animation should slow down for
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Config")
	float MaxDistance;

	//Min Range of Distance the animation should slow down for
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Config")
	float MinDistance;

	//Max play Rate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Config")
	float MaxPlayRate;

	//Min play Rate. (Dont go below 0.2, 0.0 would stop the montage)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Config")
	float MinPlayRate;

public:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference) override;

private:

	UPROPERTY()
	float LowestPlayRate = 0.2f;

	UPROPERTY()
	FVector StartPlayerLocation;
};
