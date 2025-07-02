// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "Mojing.generated.h"

UCLASS()
class MYGAME_API UMojing : public UAbility
{
	GENERATED_BODY()

public:
	virtual void InitializeAbility(AGamePlayer* Player, ACard* Card) override;
	virtual void OnTurnEnd() override;
	virtual void GrowUp() override;
};
