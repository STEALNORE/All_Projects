// Fill out your copyright notice in the Description page of Project Settings.


#include "FFCS_ANS_SlowDownRate.h"

UFFCS_ANS_SlowDownRate::UFFCS_ANS_SlowDownRate()
{
	MinPlayRate = 0.2f;
	Debug = false;
}

void UFFCS_ANS_SlowDownRate::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	MinPlayRate = FMath::Max(MinPlayRate, LowestPlayRate);
	
	if(MeshComp && Animation)
	{
		StartPlayerLocation = MeshComp->GetOwner()->GetActorLocation();
	}
}

void UFFCS_ANS_SlowDownRate::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if(MeshComp && Animation)
	{
		float Distance = FVector::Dist(StartPlayerLocation, MeshComp->GetOwner()->GetActorLocation());
		float PlayRate = FMath::GetMappedRangeValueClamped(FVector2D(MinDistance, MaxDistance), FVector2D(MaxPlayRate, MinPlayRate), Distance);
		
		if(Distance >= MinDistance && Distance <= MaxDistance)
		{
			Animation->RateScale = PlayRate;
			
		}
		if(Debug == true)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, FString::SanitizeFloat(Distance), true);
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::SanitizeFloat(PlayRate), true);
			}
		}
	}
	
}

void UFFCS_ANS_SlowDownRate::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if(MeshComp && Animation)
	{
		Animation->RateScale = MaxPlayRate;
	}
}
