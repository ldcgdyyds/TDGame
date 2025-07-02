// Fill out your copyright notice in the Description page of Project Settings.

#include "EventCenter.h"
#include "Ability.h"

TMap<FString, FPlayerEvent>& UEventCenter::PlayerEventMap()
{
    static TMap<FString, FPlayerEvent> EventMap;
    return EventMap;
}

TMap<FString, FCardEvent>& UEventCenter::CardEventMap()
{
    static TMap<FString, FCardEvent> EventMap;
    return EventMap;
}

void UEventCenter::AddListener(const FString EventName, UAbility* Ability)
{
    if(AbilityMap.Contains(EventName))
    {
        if(AbilityMap.Find(EventName)->Contains(Ability)) return;
        AbilityMap.Find(EventName)->Add(Ability);
    }
    else AbilityMap.Add(EventName, {Ability});
}

void UEventCenter::RemoveListener(const FString EventName, UAbility* Ability)
{
    if(AbilityMap.Contains(EventName)) AbilityMap.Find(EventName)->Remove(Ability);
}

void UEventCenter::Trigger(const FString EventName, ACard* Card)
{
    if(AbilityMap.Contains(EventName))
    {
        TArray<UAbility*> AbilityList=*AbilityMap.Find(EventName);
        for (int i = 0; i < AbilityList.Num(); i++)
        {
            AbilityList[i]->OnTrigger(Card);
        }
    }
}

FPlayerEvent& UEventCenter::GetPlayerEvent(const FString EventName)
{
    FPlayerEvent PlayerEvent;
    if(!PlayerEventMap().Contains(EventName)) PlayerEventMap().Add(EventName, {PlayerEvent});
    return *PlayerEventMap().Find(EventName);
}

FCardEvent& UEventCenter::GetCardEvent(const FString EventName)
{
    FCardEvent CardEvent;
    if(!CardEventMap().Contains(EventName)) CardEventMap().Add(EventName, {CardEvent});
    return *CardEventMap().Find(EventName);
}

void UEventCenter::ClearEvents()
{
    
}

