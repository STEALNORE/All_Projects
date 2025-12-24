// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_BD_Teleport.generated.h"

/**
 * 
 */
UCLASS()
class FFCS_API UANS_BD_Teleport : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	//virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	float Offset = 50.0f;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	float InterpSpeed = 5.0f;
};
