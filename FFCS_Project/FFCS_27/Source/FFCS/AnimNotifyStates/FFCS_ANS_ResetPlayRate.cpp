// Fill out your copyright notice in the Description page of Project Settings.


#include "FFCS_ANS_ResetPlayRate.h"

UFFCS_ANS_ResetPlayRate::UFFCS_ANS_ResetPlayRate()
{
	MinPlayRate = 0.2f;
}

void UFFCS_ANS_ResetPlayRate::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	MinPlayRate = FMath::Max(MinPlayRate, LowestPlayRate);

	if(MeshComp && Animation)
	{
		StartPlayerLocation = MeshComp->GetOwner()->GetActorLocation();
	}
}

void UFFCS_ANS_ResetPlayRate::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	
	if(MeshComp && Animation)
	{
		float Distance = FVector::Dist(StartPlayerLocation, MeshComp->GetOwner()->GetActorLocation());
		float PlayRate = FMath::GetMappedRangeValueClamped(FVector2D(MinDistance, MaxDistance), FVector2D(MinPlayRate, MaxPlayRate), Distance);
		if(Distance >= MinDistance && Distance <= MaxDistance)
		{
			Animation->RateScale = PlayRate;
		}
		if(Debug == true)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::SanitizeFloat(Distance), true);
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, FString::SanitizeFloat(PlayRate), true);
			}
		}
	}
}

void UFFCS_ANS_ResetPlayRate::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if(MeshComp && Animation)
	{
		Animation->RateScale = MaxPlayRate;
	}
}
