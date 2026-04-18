// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_BD_Teleport.h"

#include "FFCS/ActorComponent/AC_FFCC_Base.h"
#include "Kismet/KismetMathLibrary.h"

void UANS_BD_Teleport::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if(MeshComp->GetOwner())
	{
		UAC_FFCC_Base* FFCC = Cast<UAC_FFCC_Base>(MeshComp->GetOwner()->GetComponentByClass(UAC_FFCC_Base::StaticClass())); 
		if(FFCC)
		{
			if(FFCC->GetCurrentEnemy())
			{
				FVector StartLoc = MeshComp->GetOwner()->GetActorLocation();
				FVector EndLoc = FFCC->GetCurrentEnemy()->GetActorLocation();
				FVector Direction = (StartLoc - EndLoc).GetSafeNormal();
				FVector TeleportLoc = EndLoc + (Direction * Offset);
				FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLoc, EndLoc);
				FVector InterpLoc = FMath::VInterpTo(StartLoc, TeleportLoc, FrameDeltaTime, InterpSpeed);
				FFCC->GetCurrentEnemy()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(EndLoc, StartLoc));
				MeshComp->GetOwner()->SetActorLocationAndRotation(InterpLoc,LookAtRotation);
			}

		}
	}
}
