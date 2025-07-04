// Fill out your copyright notice in the Description page of Project Settings.


#include "TDMgr.h"

#include "UI/MainPanel.h"
#include "UI/SelectPanel.h"
#include "UI/TDPanel.h"

// Sets default values
ATDMgr::ATDMgr()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATDMgr::BeginPlay()
{
	Super::BeginPlay();
	TSubclassOf<UTDPanel> WidgetClass=LoadClass<UUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/BP_TD.BP_TD_C'"));
	TDPanel=(UTDPanel*)CreateWidget(GetWorld(), WidgetClass);
	TDPanel->AddToViewport();
	TDPanel->MainPanel->BtnStart->OnClicked.AddDynamic(this, &ATDMgr::StartGame);
	TDPanel->MainPanel->BtnQuit->OnClicked.AddDynamic(this, &ATDMgr::QuitGame);
	TDPanel->SelectPanel->BtnBack->OnClicked.AddDynamic(this, &ATDMgr::BackToMain);
}

void ATDMgr::StartGame()
{
	TDPanel->StartGame();
}

void ATDMgr::BackToMain()
{
	TDPanel->BackToMain();	
}

void ATDMgr::QuitGame()
{
	TDPanel->QuitGame();
}
