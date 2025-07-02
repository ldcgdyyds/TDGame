// Fill out your copyright notice in the Description page of Project Settings.

#include "CardPool.h"
#include "Card.h"

void UCardPool::DestroyCard(ACard* Card)
{
	
}

ACard* UCardPool::SpawnCard(AActor* ActorRef, FVector3d Location)
{
	ACard* Card;
	if(CardPool.Num()>0)
	{
		Card=CardPool[0];
		Card->SetActorLocation(Location);
	}
	else
	{
		TSubclassOf<ACard> BPCard=LoadClass<ACard>(nullptr,TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BPCard.BPCard_C'"));
		Card=ActorRef->GetWorld()->SpawnActor<ACard>(BPCard, Location, FRotator3d(0,0,0));
	}
	return Card;
}
