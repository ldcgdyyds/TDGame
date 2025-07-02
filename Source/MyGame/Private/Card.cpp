// Fill out your copyright notice in the Description page of Project Settings.

#include "Card.h"
#include "GamePlayer.h"
#include "Ability.h"
#include "UI/CardUI.h"
#include "UI/GameUI.h"
#include "EventCenter.h"
#include "CardPool.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"

// Sets default values
ACard::ACard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Widget=CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetupAttachment(RootComponent);
	Widget->SetWidgetSpace(EWidgetSpace::Screen);
}

// Called when the game starts or when spawned
void ACard::BeginPlay()
{
	Super::BeginPlay();
	EventCenter=GetWorld()->GetGameInstance()->GetSubsystem<UEventCenter>();
	CardPool=GetWorld()->GetGameInstance()->GetSubsystem<UCardPool>();
	CreateCard();
}

void ACard::BeTarget()
{
	//PlayerRef->GameUI->PanelBtn->SetVisibility(ESlateVisibility::Collapsed);
	EventCenter->Trigger("选中目标", this);
}

void ACard::StartDrag()
{
	GetWorldTimerManager().SetTimer(CardTimerHandle, this, &ACard::SetLocation, 0.01f, true);
}

void ACard::EndDrag()
{
	GetWorldTimerManager().ClearTimer(CardTimerHandle);
	if(CardState==ECardState::Hand)
	{
		if(GetActorLocation().Z>400)
		{
			PlayerRef->SellCard(this);
		}
		else
		{
			for (int i = 0; i < 6; i++)
			{
				if(FVector3d::Distance(GetActorLocation(), PlayerRef->FriendlySlots[i])<120
				&&PlayerRef->FieldList[i]==nullptr)
				{	
					SetActorLocation(PlayerRef->FriendlySlots[i]);
					CardLocation=PlayerRef->FriendlySlots[i];
					TransMinion();
					PlayerRef->PlayCard(this, i);
					return;
				}
			}
			SetActorLocation(CardLocation);
		}
	}
	else if(CardState==ECardState::Shop)
	{
		if(GetActorLocation().Z<-400)
		{
			PlayerRef->PurchaseCard(this);
		}
		else
		{
			SetActorLocation(CardLocation);
		}
	}
	else
	{
		if(GetActorLocation().Z>400)
		{
			PlayerRef->SellCard(this);
		}
		else
		{
			for (int i = 0; i < 6; i++)
			{
				if(FVector3d::Distance(GetActorLocation(), PlayerRef->FriendlySlots[i])<120)
				{
					if(PlayerRef->FieldList[i]!=nullptr)
					{
						PlayerRef->FieldList[i]->SetActorLocation(CardLocation);
						PlayerRef->FieldList[i]->CardLocation=CardLocation;
					}	
					SetActorLocation(PlayerRef->FriendlySlots[i]);
					CardLocation=PlayerRef->FriendlySlots[i];
				}
			}
		}
	}
}

void ACard::SetLocation()
{
	FVector2D MousePosition=UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	SetActorLocation(FVector3d((540-MousePosition.X),0,(1170-MousePosition.Y)));
}

void ACard::InitializeCard(AGamePlayer* Player, FCardInfo* CardInfo, bool Gold)
{
	PlayerRef=Player;
	Id=CardInfo->Id;
	Name=CardInfo->Name;
	Star=CardInfo->Star;
	Icon=CardInfo->Icon;
	Attack=CardInfo->Attack;
	Health=CardInfo->Health;
	AttackBase=Attack;
	HealthBase=Health;
	bGold=Gold;
	TSubclassOf<UAbility> AbilityClass=LoadClass<UAbility>(nullptr,*CardInfo->Ability);
	Ability=NewObject<UAbility>(this, AbilityClass);
	Ability->InitializeAbility(Player, this);
	CardUI->InitializeCard(Star, Icon, Attack, Health, bGold);
}

void ACard::TransCard()
{
	CreateCard();
	CardUI->InitializeCard(Star, Icon, Attack, Health, bGold);
}

void ACard::TransMinion()
{
	CreateMinion();
	CardUI->InitializeCard(Star, Icon, Attack, Health, bGold);
}

void ACard::RandomMinion(FCardInfo* CardInfo, bool Gold)
{
	Star=CardInfo->Star;
	Icon=CardInfo->Icon;
	Attack=CardInfo->Attack;
	Health=CardInfo->Health;
	bGold=Gold;
	CreateMinion();
	CardUI->InitializeCard(Star, Icon, Attack, Health, bGold);
}

void ACard::CopyMinion(int32 PStar, UTexture2D* PIcon, int32 PAttack, int32 PHealth, bool Gold)
{
	Star=PStar;
	Icon=PIcon;
	Attack=PAttack;
	Health=PHealth;
	bGold=Gold;
	CreateMinion();
	CardUI->InitializeCard(Star, Icon, Attack, Health, bGold);
}

void ACard::SettleDamage(ACard* Card)
{
	Health-=Card->Attack;
	CardUI->UpdateInjury(Health);
	if(Health<=0) bDead=true;
}

void ACard::BeOptions()
{
	CardUI->CardBtn->OnClicked.AddDynamic(this, &ACard::BeTarget);
}

void ACard::BeNormal()
{
	CardUI->CardBtn->OnClicked.Clear();
}

void ACard::OnStateUpdate(ECardState NewCardState)
{
	CardState=NewCardState;
	Ability->OnStateUpdate();
}

void ACard::OnPurchase()
{
	Ability->OnPurchase();
}

void ACard::OnSell()
{
	Ability->OnSell();
}

void ACard::OnPlay()
{
	Ability->OnPlay();
}

void ACard::OnTurnEnd()
{
	Ability->OnTurnEnd();
}

void ACard::OnAttack(ACard* Card)
{
	Ability->OnAttack(Card);
}

void ACard::OnDestroy(ECardState NewCardState)
{
	//OnStateUpdate(NewCardState);
	Destroy();
}

void ACard::CreateCard()
{
	Widget->SetDrawSize(FVector2d(304,444));
	TSubclassOf<UCardUI> WidgetClass=LoadClass<UUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WB_Card.WB_Card_C'"));
	CardUI=(UCardUI*)CreateWidget(GetWorld(), WidgetClass);
	Widget->SetWidget(CardUI);
	CardUI->CardBtn->OnPressed.AddDynamic(this, &ACard::StartDrag);
	CardUI->CardBtn->OnReleased.AddDynamic(this, &ACard::EndDrag);
}

void ACard::CreateMinion()
{
	Widget->SetDrawSize(FVector2d(210,280));
	TSubclassOf<UCardUI> WidgetClass=LoadClass<UUserWidget>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WB_Creature.WB_Creature_C'"));
	CardUI=(UCardUI*)CreateWidget(GetWorld(), WidgetClass);
	Widget->SetWidget(CardUI);
	CardUI->CardBtn->OnPressed.AddDynamic(this, &ACard::StartDrag);
	CardUI->CardBtn->OnReleased.AddDynamic(this, &ACard::EndDrag);
}
