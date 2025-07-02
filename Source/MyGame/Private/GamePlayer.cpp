// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlayer.h"
#include "Card.h"
#include "Ability.h"
#include "UI/GameUI.h"
#include "UI/MainUI.h"
#include "UI/CardUI.h"
#include "EventCenter.h"
#include "CardPool.h"
#include "Components/WidgetComponent.h"

// Sets default values
AGamePlayer::AGamePlayer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Widget=CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(RootComponent);
	Widget->SetWidgetSpace(EWidgetSpace::Screen);
	Widget->SetDrawSize(FVector2d(1280,720));
	for (int i = 0; i < 3; i++)
	{
		ShopSlots[i]=FVector3d(332-i*332,0,628);
	}	
	for (int i = 0; i < 7; i++)
	{
		HandSlots[i]=FVector3d(240-i*80,0,-910);
	}
	for (int i = 0; i < 6; i++)
	{
		if(i<3) EnemySlots[i]=FVector3d(300-i*300,0,408);
		else EnemySlots[i]=FVector3d(300-(i-3)*300,0,738);
	}
	for (int i = 0; i < 6; i++)
	{
		if(i<3) FriendlySlots[i]=FVector3d(300-i*300,0,50);
		else FriendlySlots[i]=FVector3d(300-(i-3)*300,0,-280);
	}
	FieldList.SetNum(6);
	EnemyList.SetNum(6);
	FriendlyList.SetNum(6);			
	TurnTimes=20, CurCoins=10, Level=3, LevelUpCost=5, RefreshCost=1, LockCost=0, Health=40;
	CurEnemy=0, CurFriendly=0;
	bLock=false, bBattle=false;
}

// Called when the game starts or when spawned
void AGamePlayer::BeginPlay()
{
	Super::BeginPlay();
	EventCenter=GetWorld()->GetGameInstance()->GetSubsystem<UEventCenter>();
	CardPool=GetWorld()->GetGameInstance()->GetSubsystem<UCardPool>();
	CardDataTable=LoadObject<UDataTable>(this, TEXT("/Script/Engine.DataTable'/Game/Data/DTCard.DTCard'"));
	CardNames=CardDataTable->GetRowNames();
	TSubclassOf<UMainUI> WidgetClass=LoadClass<UUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WB_LuckMain.WB_LuckMain_C'"));
	MainUI=(UMainUI*)CreateWidget(GetWorld(), WidgetClass);
	Widget->SetWidget(MainUI);
	/*StartUI->HeroBtn1->OnClicked.AddDynamic(this, &AGamePlayer::StartGame);
	StartUI->HeroBtn2->OnClicked.AddDynamic(this, &AGamePlayer::StartGame);
	StartUI->HeroBtn3->OnClicked.AddDynamic(this, &AGamePlayer::StartGame);
	StartUI->HeroBtn4->OnClicked.AddDynamic(this, &AGamePlayer::StartGame);*/
}

void AGamePlayer::BeTarget()
{
	//GameUI->PanelBtn->SetVisibility(ESlateVisibility::Collapsed);
	EventCenter->Trigger("选中目标", nullptr);
}

void AGamePlayer::StartGame()
{
	TSubclassOf<UGameUI> WidgetClass=LoadClass<UUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WB_Game.WB_Game_C'"));
	GameUI=(UGameUI*)CreateWidget(GetWorld(), WidgetClass);
	Widget->SetWidget(GameUI);
	//GameUI->LevelUpBtn->OnClicked.AddDynamic(this, &AGamePlayer::LevelUp);
	//GameUI->RefreshBtn->OnClicked.AddDynamic(this, &AGamePlayer::Refresh);
	//GameUI->LockBtn->OnClicked.AddDynamic(this, &AGamePlayer::Lock);
	//GameUI->PanelBtn->OnClicked.AddDynamic(this, &AGamePlayer::BeTarget);
	//GameUI->InitializeGame(TurnTimes, CurCoins, Level, LevelUpCost, RefreshCost, LockCost, Health);
	StartTimer();
	Refresh();
}

void AGamePlayer::StartTimer()
{
	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AGamePlayer::Timer, 1.0f, true);
}

void AGamePlayer::Timer()
{
	TurnTimes-=1;
	//GameUI->UpdateTimer(TurnTimes);
	if(TurnTimes==0)
	{
		GetWorldTimerManager().ClearTimer(GameTimerHandle);
		GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AGamePlayer::EndTurn, 1.0f);
		for (int i = 0; i < 6; i++)
		{
			if(FieldList[i]!=nullptr)
			{
				FieldList[i]->OnTurnEnd();
			}
		}
	}
}

void AGamePlayer::LevelUp()
{
	if(Level<6&&CurCoins>=LevelUpCost)
	{
		CurCoins-=LevelUpCost;
		Level+=1;
		LevelUpCost=Level+5;
		//GameUI->UpdateCoins(CurCoins);
		//GameUI->UpdateLevel(Level);
		//GameUI->UpdateLevelupcost(LevelUpCost);
	}
}

void AGamePlayer::Refresh()
{
	if(ShopList.Num()>0)
	{
		for (ACard* Card : ShopList)
		{
			Card->Destroy();
		}		
		ShopList.Empty();
	}
	for (int i = 0; i < 3; i++)
	{
		int32 RandomIndex=FMath::RandRange(0, CardNames.Num()-1);
		FCardInfo* CardInfo=CardDataTable->FindRow<FCardInfo>(CardNames[RandomIndex], TEXT("CardInfo"));
		ACard* Card=CardPool->SpawnCard(this, ShopSlots[i]);
		Card->InitializeCard(this, CardInfo, false);
		Card->CardLocation=ShopSlots[i];
		ShopList.Add(Card);
		Card->OnStateUpdate(ECardState::Shop);
	}	
}

void AGamePlayer::Lock()
{
	for (ACard* Card : ShopList)
	{
		Card->CardUI->UpdateLock(bLock);
	}
	bLock=!bLock;
}

void AGamePlayer::PurchaseCard(ACard* Card)
{
	ShopList.Remove(Card);
	int i=HandList.Add(Card);
	Card->OnStateUpdate(ECardState::Hand);
	Card->CardLocation=HandSlots[i];
	Card->SetActorLocation(HandSlots[i]);
	GainCard(Card);
	Card->OnPurchase();
	CheckTriple(Card);
}

void AGamePlayer::SellCard(ACard* Card)
{
	if(Card->CardState==ECardState::Hand) HandList.Remove(Card);
	else FieldList[FieldList.Find(Card)]=nullptr;
	LoseCard(Card);
	Card->OnDestroy(ECardState::Pool);
}

void AGamePlayer::PlayCard(ACard* Card, int32 Index)
{
	HandList.Remove(Card);
	FieldList[Index]=Card;
	Card->OnStateUpdate(ECardState::Field);
	Card->OnPlay();
}

void AGamePlayer::SettleDamage(AGamePlayer* Player)
{
	int32 TotalDamage=0;
	for (int i = 0; i < 6; i++)
	{
		if(EnemyList[i]!=nullptr) TotalDamage+=EnemyList[i]->Star;
	}
	TotalDamage+=Level;
	Health-=TotalDamage;
	//GameUI->UpdateInjury(Health);
	if(Health<=0) bDead=true;
}

void AGamePlayer::ClearField(TArray<ACard*> CardList)
{
	for (int i = 0; i < 6; i++)
	{
		if(CardList[i]!=nullptr)
		{
			CardList[i]->OnDestroy(ECardState::Pool);
			CardList[i]=nullptr;
		}
	}
}

void AGamePlayer::StartTurn()
{
	GetWorldTimerManager().ClearTimer(GameTimerHandle);
	bBattle=false;
	TurnTimes=10;
	SwitchPanel();
	StartTimer();
	if(bLock) Lock();
	else Refresh();
}

void AGamePlayer::EndTurn()
{
	GetWorldTimerManager().ClearTimer(GameTimerHandle);
	bBattle=true;
	SwitchPanel();
	ReadyBattle();
	StartBattle();
}

void AGamePlayer::ReadyBattle()
{
	for (int i = 0; i < 3; i++)
	{
		int32 RandomIndex=FMath::RandRange(0, CardNames.Num()-1);
		FCardInfo* CardInfo=CardDataTable->FindRow<FCardInfo>(CardNames[RandomIndex], TEXT("CardInfo"));
		ACard* Card=CardPool->SpawnCard(this, EnemySlots[i]);
		Card->RandomMinion(CardInfo, false);
		Card->CardLocation=EnemySlots[i];
		EnemyList[i]=Card;
	}
	for (int i = 0; i < 6; i++)
	{
		if(FieldList[i]!=nullptr)
		{
			ACard* Card=CardPool->SpawnCard(this, FieldList[i]->CardLocation);
			Card->CopyMinion(FieldList[i]->Star, FieldList[i]->Icon, FieldList[i]->Attack, FieldList[i]->Health, false);
			Card->CardLocation=FieldList[i]->CardLocation;
			FriendlyList[i]=Card;
		}
	}
}

void AGamePlayer::StartBattle()
{
	bAttack=FMath::RandBool();
	SettleBattle();
}

void AGamePlayer::GoBattle()
{
	if(bAttack)
	{
		while(FriendlyList[CurFriendly]==nullptr)
		{
			SetCurAttack(CurFriendly);
		}
		Target=SelectTarget(EnemyList);
		//FriendlyList[CurFriendly]->OnAttack(EnemyList[Target]);
		if(FriendlyList[CurFriendly]) GoAttack(FriendlyList[CurFriendly]);
	}
	else
	{
		while(EnemyList[CurEnemy]==nullptr)
		{
			SetCurAttack(CurEnemy);
		}
		Target=SelectTarget(FriendlyList);
		//EnemyList[CurEnemy]->OnAttack(FriendlyList[Target]);
		if(EnemyList[CurEnemy]) GoAttack(EnemyList[CurEnemy]);
	}
}

void AGamePlayer::UpdatePosition(ACard* Card, float Value)
{
	if(bAttack) Card->SetActorLocation(FMath::Lerp(FriendlySlots[CurFriendly], EnemySlots[Target], Value));
	else Card->SetActorLocation(FMath::Lerp(EnemySlots[CurEnemy], FriendlySlots[Target], Value));
}

void AGamePlayer::FinishAttack()
{
	if(bAttack)
	{
		EnemyList[Target]->SettleDamage(FriendlyList[CurFriendly]);
		FriendlyList[CurFriendly]->SettleDamage(EnemyList[Target]);
		if(FriendlyList[CurFriendly]->bDead)
		{
			FriendlyList[CurFriendly]->OnDestroy(ECardState::Pool);
			FriendlyList[CurFriendly]=nullptr;
		}
		if(EnemyList[Target]->bDead)
		{
			EnemyList[Target]->OnDestroy(ECardState::Pool);
			EnemyList[Target]=nullptr;
		}
		SetCurAttack(CurFriendly);
		bAttack=false;
	}
	else
	{
		FriendlyList[Target]->SettleDamage(EnemyList[CurEnemy]);
		EnemyList[CurEnemy]->SettleDamage(FriendlyList[Target]);
		if(EnemyList[CurEnemy]->bDead)
		{
			EnemyList[CurEnemy]->OnDestroy(ECardState::Pool);
			EnemyList[CurEnemy]=nullptr;
		}
		if(FriendlyList[Target]->bDead)
		{
			FriendlyList[Target]->OnDestroy(ECardState::Pool);
			FriendlyList[Target]=nullptr;
		}
		SetCurAttack(CurEnemy);
		bAttack=true;
	}
	SettleBattle();
}

void AGamePlayer::CheckTriple(ACard* Card)
{
	if(!Card->Ability->Ditto)
	{
		EventCenter->Trigger("检查三连", Card);
		if(CardMap.Find(Card->Id)->Num()==3) Triple(Card->Name);
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			if(FieldList[i]!=nullptr)
			{
				EventCenter->Trigger("检查三连", FieldList[i]);
				if(CardMap.Find(FieldList[i]->Id)->Num()==3)
				{
					Triple(FieldList[i]->Name);
					return;
				}
			}
		}
		for (ACard* HandCard : HandList)
		{
			EventCenter->Trigger("检查三连", HandCard);
			if(CardMap.Find(HandCard->Id)->Num()==3)
			{
				Triple(HandCard->Name);
				return;
			}
		}
	}
}

void AGamePlayer::Triple(FName Name)
{
	FCardInfo* CardInfo=CardDataTable->FindRow<FCardInfo>(Name, TEXT("CardInfo"));
	ACard* GoldCard=CardPool->SpawnCard(this, FVector3d(0,0,0));
	GoldCard->InitializeCard(this, CardInfo, true);
	TArray<ACard*> Cards=*CardMap.Find(GoldCard->Id);
	CombineProp(Cards, GoldCard);
	for (ACard* Card : Cards)
	{
		if(HandList.Contains(Card)) HandList.Remove(Card);
		else FieldList[FieldList.Find(Card)]=nullptr;
		Card->OnDestroy(ECardState::Pool);
	}
	CardMap.Find(GoldCard->Id)->Empty();
	int i=HandList.Add(GoldCard);
	GoldCard->OnStateUpdate(ECardState::Hand);
	GoldCard->CardLocation=HandSlots[i];
	GoldCard->SetActorLocation(HandSlots[i]);
}

void AGamePlayer::DestroyCard(ACard* Card)
{
	Card->OnDestroy(ECardState::Pool);
}

void AGamePlayer::SwitchPanel()
{
	//GameUI->UpdatePanel(bBattle);
	for (ACard* Card : ShopList)
	{
		Card->CardUI->UpdateCard(bBattle);
	}
	for (int i = 0; i < 6; i++)
	{
		if(FieldList[i]!=nullptr) FieldList[i]->CardUI->UpdateCard(bBattle);
	}	
}

void AGamePlayer::SettleBattle()
{
	bool ExistFriendly=false, ExistEnemy=false;
	for (int i = 0; i < 6; i++)
	{
		if(FriendlyList[i]!=nullptr)
		{
			ExistFriendly=true;
			break;
		}
	}
	for (int i = 0; i < 6; i++)
	{
		if(EnemyList[i]!=nullptr)
		{
			ExistEnemy=true;
			break;
		}
	}
	if(ExistFriendly&&ExistEnemy) GoBattle();
	else
	{
		if(ExistFriendly)
		{
			ClearField(FriendlyList);
		}
		else if(ExistEnemy)
		{
			SettleDamage(this);
			ClearField(EnemyList);
		}
		GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AGamePlayer::StartTurn, 1.0f);
	}
}

void AGamePlayer::SetCurAttack(int32 &Index)
{
	Index+=1;
	if(Index==6) Index=0;
}

int AGamePlayer::SelectTarget(TArray<ACard*> CardList)
{
	TArray<int> ValidTarget;
	for (int i = 0; i < 3; i++)
	{
		if(CardList[i]!=nullptr) ValidTarget.Add(i);
	}
	if(ValidTarget.Num()>0) return ValidTarget[FMath::RandRange(0, ValidTarget.Num()-1)];
	else
	{
		for (int i = 3; i < 6; i++)
		{
			if(CardList[i]!=nullptr) ValidTarget.Add(i);
		}
		return ValidTarget[FMath::RandRange(0, ValidTarget.Num()-1)];
	}
}

void AGamePlayer::GainCard(ACard* Card)
{
	if(CardMap.Contains(Card->Id)) CardMap.Find(Card->Id)->Add(Card);
	else CardMap.Add(Card->Id, {Card});
}

void AGamePlayer::LoseCard(ACard* Card)
{
	CardMap.Find(Card->Id)->Remove(Card);
}

void AGamePlayer::CombineProp(TArray<ACard*> Cards, ACard* GoldCard)
{
	int32 AttackBuff=0, HealthBuff=0;
	for (ACard* Card : Cards)
	{
		AttackBuff+=Card->Attack;
		AttackBuff-=Card->AttackBase;
		HealthBuff+=Card->Health;
		HealthBuff-=Card->HealthBase;
	}
	GoldCard->Attack=AttackBuff+GoldCard->Attack*2;
	GoldCard->Health=HealthBuff+GoldCard->Health*2;
	GoldCard->CardUI->UpdateAttack(GoldCard->Attack);
	GoldCard->CardUI->UpdateHealth(GoldCard->Health);
}