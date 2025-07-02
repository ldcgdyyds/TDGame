// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability/Witch.h"
#include "GamePlayer.h"
#include "Card.h"

void UWitch::InitializeAbility(AGamePlayer* Player, ACard* Card)
{
	Super::InitializeAbility(Player, Card);
}

void UWitch::OnAttack(ACard* Card)
{
	PlayerRef->DestroyCard(CardRef);
	PlayerRef->DestroyCard(Card);
}
