// Fill out your copyright notice in the Description page of Project Settings.

#include "LuckMgr.h"
#include "LuckData.h"
#include "UI/MainPanel.h"
#include "UI/SelectPanel.h"
#include "UI/GameUI.h"

// Sets default values
ALuckMgr::ALuckMgr()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALuckMgr::BeginPlay()
{
	Super::BeginPlay();
	LuckCardDataTable=LoadObject<UDataTable>(this, TEXT("/Script/Engine.DataTable'/Game/Data/DT_LuckCardInfo.DT_LuckCardInfo'"));
	LuckCardNames=LuckCardDataTable->GetRowNames();
}

