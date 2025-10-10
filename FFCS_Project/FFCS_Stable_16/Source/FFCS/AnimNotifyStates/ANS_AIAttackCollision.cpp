// Fill out your copyright notice in the Description page of Project Settings.

#include "ANS_AIAttackCollision.h"
#include "FFCS/ActorComponent/AC_FFCC_Base.h"
#include "Kismet/KismetSystemLibrary.h"


void UANS_AIAttackCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
   Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

   //Saving to a variable. to the value resets to what we set in the ANS
   AttackOnceTrigger = DoAttackOnce;
}

void UANS_AIAttackCollision::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
   Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

   if(AttackOnceTrigger)
   {
      //If Attack Should Be done only once, use the private variable that gets reset at Begin Notify to check
      DoCollisionCheck(MeshComp);
      AttackOnceTrigger = false;
   }
   else if(!DoAttackOnce)
   {
      //If Attack can be triggered multiple times, than use the exposed variable since the private gets set to false when it is true, that means it will coninue to run the multiple hit logic after attacking once
      DoCollisionCheck(MeshComp);
   }
}

void UANS_AIAttackCollision::DoCollisionCheck(USkeletalMeshComponent* MeshComp)
{
   //Creating HitResult Variable
   FHitResult HitResult;

   //Values for SphereTraceSingle
   const FVector InSocket = MeshComp->GetSocketLocation(StartSocket);
   const FVector OutSocket = MeshComp->GetSocketLocation(EndSocket);

   //Converting TraceType to TraceQuery
   const ETraceTypeQuery TraceChannel = UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1);

   //Creating a variable for Actors Array
   TArray<AActor*> ActorsToIgnore;

   //Adding Actors to the Array
   ActorsToIgnore.Add(MeshComp->GetOwner());

   //Variable for Trace Debug
   EDrawDebugTrace::Type DoTrace;

   //Set Debug Type Based on Debug bool Exposed to the ANS
   if (Debug)
   {
      DoTrace = EDrawDebugTrace::ForDuration;
   }
   else
   {
      DoTrace = EDrawDebugTrace::None;
   }

   bool bHit = UKismetSystemLibrary::SphereTraceSingle(MeshComp->GetWorld(), InSocket, OutSocket, Radius, TraceChannel, true, ActorsToIgnore, DoTrace, HitResult, true);

   const AActor* HitActor = HitResult.GetActor();
   if (bHit)
   {
      if(HitActor && HitResult.GetActor()->GetComponentByClass(UAC_FFCC_Base::StaticClass()))
      {

         //Print String
         FString HitActorName = HitActor->GetName();
         GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Hit actor: %s"), *HitActorName));

         UAC_FFCC_Base* FFCS = Cast<UAC_FFCC_Base>(HitActor->GetComponentByClass(UAC_FFCC_Base::StaticClass()));
         EAttackHitDirection HitDirection = FFCS->HitDirection(MeshComp->GetOwner());
         if(HitDirection)
         {
            FFCS->PlayHitMontage(HitDirection);
         }
         else
         {
            FFCS->PlayHitMontage(EAttackHitDirection::Fwd);
         }
      }
   }
}