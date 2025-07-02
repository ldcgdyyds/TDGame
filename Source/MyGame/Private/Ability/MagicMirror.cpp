// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability/MagicMirror.h"
#include "GamePlayer.h"
#include "Card.h"
#include "EventCenter.h"

void UMagicMirror::InitializeAbility(AGamePlayer* Player, ACard* Card)
{
	Super::InitializeAbility(Player, Card);
	Ditto=true;
}

void UMagicMirror::OnTrigger(ACard* Card)
{
	if(PlayerRef->CardMap.Find(Card->Id)->Num()==3) return;
	if(Card->Star>=4&&Card->Id!=CardRef->Id&&PlayerRef->CardMap.Find(Card->Id)->Num()
	+PlayerRef->CardMap.Find(CardRef->Id)->Num()==3)
	{
		PlayerRef->CardMap.Find(Card->Id)->Append(*PlayerRef->CardMap.Find(CardRef->Id));
		PlayerRef->CardMap.Find(CardRef->Id)->Empty();
	}
}

void UMagicMirror::OnStateUpdate()
{
	if(CardRef->CardState==ECardState::Hand||CardRef->CardState==ECardState::Field)
		EventCenter->AddListener("检查三连", this);
	else
		EventCenter->RemoveListener("检查三连", this);
}
