// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability.h"
#include "GamePlayer.h"
#include "Card.h"
#include "EventCenter.h"
#include "CardPool.h"

void UAbility::InitializeAbility(AGamePlayer* Player, ACard* Card)
{
	PlayerRef=Player;
	CardRef=Card;
	EventCenter=PlayerRef->GetWorld()->GetGameInstance()->GetSubsystem<UEventCenter>();
	CardPool=GetWorld()->GetGameInstance()->GetSubsystem<UCardPool>();
}

void UAbility::OnTrigger(ACard* Card)
{
	
}

void UAbility::OnStateUpdate()
{
	
}

void UAbility::OnPurchase()
{
	EventCenter->Trigger("进入手牌", CardRef);
}

void UAbility::OnSell()
{
	
}

void UAbility::OnPlay()
{
	EventCenter->Trigger("入场", CardRef);
}

void UAbility::OnTurnEnd()
{
	
}

void UAbility::OnAttack(ACard* Card)
{
	
}

void UAbility::BattleCry()
{
	
}

void UAbility::GrowUp()
{
	
}

void UAbility::EnterHand()
{
	
}
