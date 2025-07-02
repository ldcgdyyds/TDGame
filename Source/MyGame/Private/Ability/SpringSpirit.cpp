// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability/SpringSpirit.h"
#include "GamePlayer.h"
#include "Card.h"
#include "EventCenter.h"

void USpringSpirit::InitializeAbility(AGamePlayer* Player, ACard* Card)
{
	Super::InitializeAbility(Player, Card);
	GrowUpTimes=1;
}

void USpringSpirit::OnTrigger(ACard* Card)
{
	if(GrowUpTimes>0)
	{
		GrowUpTimes-=1;
		Card->Ability->GrowUp();
	}
}

void USpringSpirit::OnStateUpdate()
{
	if(CardRef->CardState==ECardState::Field)
		EventCenter->AddListener("成长", this);
	else
		EventCenter->RemoveListener("成长", this);
}
