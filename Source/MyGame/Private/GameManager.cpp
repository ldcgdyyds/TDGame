// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "Ability.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGameManager::AddListener(const FString EventName, UAbility* Ability)
{
	if(AbilityMap.Contains(EventName))
	{
		if(AbilityMap.Find(EventName)->Contains(Ability)) return;
		AbilityMap.Find(EventName)->Add(Ability);
	}
	else AbilityMap.Add(EventName, {Ability});
}

void AGameManager::RemoveListener(const FString EventName, UAbility* Ability)
{
	if(AbilityMap.Contains(EventName)) AbilityMap.Find(EventName)->Remove(Ability);
}

void AGameManager::Trigger(const FString EventName, ACard* Card)
{
	if(AbilityMap.Contains(EventName))
	{
		TArray<UAbility*> AbilityList=*AbilityMap.Find(EventName);
		for (int i = 0; i < AbilityList.Num(); i++)
		{
			AbilityList[i]->OnTrigger(Card);
		}
	}
}

