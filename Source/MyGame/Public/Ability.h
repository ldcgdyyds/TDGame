// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.generated.h"

class UEventCenter;
class UCardPool;
class AGamePlayer;
class ACard;

UCLASS()
class MYGAME_API UAbility : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="EventCenter")
		UEventCenter* EventCenter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CardPool")
		UCardPool* CardPool;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player")
		AGamePlayer* PlayerRef;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Card")
		ACard* CardRef;
	bool Ditto;
	virtual void InitializeAbility(AGamePlayer* Player, ACard* Card);
	virtual void OnTrigger(ACard* Card);
	virtual void OnStateUpdate();
	virtual void OnPurchase();
	virtual void OnSell();
	virtual void OnPlay();
	virtual void OnTurnEnd();
	virtual void OnAttack(ACard* Card);
	virtual void BattleCry();
	virtual void GrowUp();
	virtual void EnterHand();
};
