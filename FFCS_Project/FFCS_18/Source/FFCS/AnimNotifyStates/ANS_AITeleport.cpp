// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_AITeleport.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

void UANS_AITeleport::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)

{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if(MeshComp->GetOwner())
	{
		//C++ equivalent of Getowner()->GetBlackboard()
		const UBlackboardComponent* BlackboardComp = UAIBlueprintHelperLibrary::GetBlackboard(MeshComp->GetOwner());
		if(BlackboardComp)
		{
			//Gets the blackboard Key Literal Name
			const FName KeyName = FName("TargetActor");

			UObject* Value = BlackboardComp->GetValueAsObject(KeyName);
			if (Value)
			{	//Cast to Character using the Value from the blackboard function GetValueAsObject
				 ACharacter* Player = Cast<ACharacter>(Value);
			

				if (Player)
				{
					FVector StartLoc = MeshComp->GetOwner()->GetActorLocation();
					FVector PlayerLoc = Player->GetActorLocation();

					FVector Direction = (StartLoc - PlayerLoc).GetSafeNormal();
					FVector TeleportLoc = PlayerLoc + (Direction * Offset);

					FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLoc, TeleportLoc);

					FVector InterpLoc = FMath::VInterpTo(StartLoc, TeleportLoc, FrameDeltaTime, InterpSpeed);
					MeshComp->GetOwner()->SetActorLocationAndRotation(InterpLoc, LookAtRotation);
				}
			}
		}
	}
}
