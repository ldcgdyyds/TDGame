// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability/SilentDoctor.h"
#include "GamePlayer.h"
#include "Card.h"
#include "UI/GameUI.h"
#include "UI/CardUI.h"
#include "EventCenter.h"

void USilentDoctor::InitializeAbility(AGamePlayer* Player, ACard* Card)
{
	Super::InitializeAbility(Player, Card);
}

void USilentDoctor::OnTrigger(ACard* Card)
{
	Buff(Card);
}

void USilentDoctor::OnPlay()
{
	BattleCry();
}

void USilentDoctor::BattleCry()
{
	for (int i = 0; i < 6; i++)
	{
		if(PlayerRef->FieldList[i]!=nullptr) PlayerRef->FieldList[i]->BeOptions();
	}
	EventCenter->AddListener("选中目标", this);
	//PlayerRef->GameUI->PanelBtn->SetVisibility(ESlateVisibility::Visible);
}

void USilentDoctor::Buff(ACard* Target)
{
	if(Target&&Target!=CardRef)
	{
		Target->Health+=15;
		Target->CardUI->UpdateHealth(Target->Health);
	}
	else
	{
		//To do
	}
	for (int i = 0; i < 6; i++)
	{
		if(PlayerRef->FieldList[i]!=nullptr) PlayerRef->FieldList[i]->BeNormal();
	}
	EventCenter->RemoveListener("选中目标", this);
}
