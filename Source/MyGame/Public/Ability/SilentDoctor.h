// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "SilentDoctor.generated.h"

UCLASS()
class MYGAME_API USilentDoctor : public UAbility
{
	GENERATED_BODY()

public:
	virtual void InitializeAbility(AGamePlayer* Player, ACard* Card) override;
	virtual void OnTrigger(ACard* Card) override;
	virtual void OnPlay() override;

protected:
	virtual void BattleCry() override;

private:
	void Buff(ACard* Target);
};
