// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability/Mojing.h"
#include "GamePlayer.h"
#include "Card.h"
#include "UI/CardUI.h"
#include "EventCenter.h"

void UMojing::InitializeAbility(AGamePlayer* Player, ACard* Card)
{
	Super::InitializeAbility(Player, Card);
}

void UMojing::OnTurnEnd()
{
	GrowUp();
}

void UMojing::GrowUp()
{
	CardRef->Attack+=1;
	CardRef->Health+=1;
	CardRef->CardUI->UpdateAttack(CardRef->Attack);
	CardRef->CardUI->UpdateHealth(CardRef->Health);
	EventCenter->Trigger("成长", CardRef);
}
