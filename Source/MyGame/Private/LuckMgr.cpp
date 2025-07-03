// Fill out your copyright notice in the Description page of Project Settings.

#include "LuckMgr.h"
#include "LuckData.h"
#include "UI/LuckUI.h"
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
	TSubclassOf<ULuckUI> WidgetClass=LoadClass<UUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/BP_Luck.BP_Luck_C'"));
	LuckUI=(ULuckUI*)CreateWidget(GetWorld(), WidgetClass);
	LuckUI->AddToViewport();
	LuckUI->LuckMainUI->BtnStart->OnClicked.AddDynamic(this, &ALuckMgr::SelectLevel);
	LuckUI->LuckLevelUI->BtnStart->OnClicked.AddDynamic(this, &ALuckMgr::StartGame);
	LuckUI->LuckLevelUI->BtnBack->OnClicked.AddDynamic(this, &ALuckMgr::BackToMain);
	LuckUI->LuckGameUI->BtnConfirm->OnClicked.AddDynamic(this, &ALuckMgr::ConfirmInfo);
	LuckUI->LuckLevelUI->InitLevel();
}

void ALuckMgr::SelectLevel()
{
	LuckUI->SelectLevel();
}

void ALuckMgr::StartGame()
{
	LuckUI->StartGame();
}

void ALuckMgr::BackToMain()
{
	LuckUI->BackToMain();
}

void ALuckMgr::ConfirmInfo()
{
	LuckUI->LuckGameUI->ConfirmInfo();
}

