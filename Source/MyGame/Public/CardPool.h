// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CardPool.generated.h"

class ACard;

UCLASS()
class MYGAME_API UCardPool : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void DestroyCard(ACard* Card);
	
	ACard* SpawnCard(AActor* ActorRef, FVector3d Location);

private:
	TArray<ACard*> CardPool;
};
