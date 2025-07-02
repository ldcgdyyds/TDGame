// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EventCenter.generated.h"

class ACard;
class UAbility;
DECLARE_MULTICAST_DELEGATE(FPlayerEvent);
DECLARE_MULTICAST_DELEGATE_OneParam(FCardEvent, ACard*);

UCLASS()
class MYGAME_API UEventCenter : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	TMap<FString, FPlayerEvent>& PlayerEventMap();

	TMap<FString, FCardEvent>& CardEventMap();

	void AddListener(const FString EventName, UAbility* Ability);

	void RemoveListener(const FString EventName, UAbility* Ability);

	void Trigger(const FString EventName, ACard* Card);

	FPlayerEvent& GetPlayerEvent(const FString EventName);

	FCardEvent& GetCardEvent(const FString EventName);

	void ClearEvents();

private:
	TMap<FString, TArray<UAbility*>> AbilityMap;
};
