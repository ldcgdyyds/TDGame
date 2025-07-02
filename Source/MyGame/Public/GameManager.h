// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

class ACard;
class UAbility;

UCLASS()
class MYGAME_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void AddListener(const FString EventName, UAbility* Ability);

	void RemoveListener(const FString EventName, UAbility* Ability);

	void Trigger(const FString EventName, ACard* Card);

private:
	TMap<FString, TArray<UAbility*>> AbilityMap;
};
