// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardData.h"
#include "GameFramework/Actor.h"
#include "GamePlayer.generated.h"

class UWidgetComponent;
class UGameUI;
class UMainPanel;
class UEventCenter;
class UCardPool;
class ACard;

UCLASS()
class MYGAME_API AGamePlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGamePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MyWidgetComponent")
		UWidgetComponent* Widget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
		UGameUI* GameUI;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
		UMainPanel* MainUI;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="EventCenter")
		UEventCenter* EventCenter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CardPool")
		UCardPool* CardPool;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="DataTable")
		UDataTable* CardDataTable;
	FVector3d ShopSlots[3];
	FVector3d HandSlots[7];
	FVector3d EnemySlots[6];
	FVector3d FriendlySlots[6];
	int32 TurnTimes, CurCoins, Level, LevelUpCost, RefreshCost, LockCost, Health;
	int32 CurFriendly, CurEnemy, Target;
	bool bLock, bBattle, bAttack, bDead;
	TArray<FName> CardNames;
	TArray<ACard*> ShopList;
	TArray<ACard*> HandList;
	TArray<ACard*> FieldList;
	TArray<ACard*> EnemyList;
	TArray<ACard*> FriendlyList;
	TMap<FString, TArray<ACard*>> CardMap;
	FTimerHandle GameTimerHandle;
	UFUNCTION(BlueprintCallable)
		void BeTarget();
	UFUNCTION(BlueprintCallable)
		void StartGame();
	void StartTimer();
	void Timer();
	UFUNCTION(BlueprintCallable)
		void LevelUp();
	UFUNCTION(BlueprintCallable)
		void Refresh();
	UFUNCTION(BlueprintCallable)
		void Lock();
	void PurchaseCard(ACard* Card);
	void SellCard(ACard* Card);
	void PlayCard(ACard* Card, int32 Index);
	void SettleDamage(AGamePlayer* Player);
	void ClearField(TArray<ACard*> CardList);
	void StartTurn();
	void EndTurn();
	void ReadyBattle();
	void StartBattle();
	void GoBattle();
	UFUNCTION(BlueprintImplementableEvent)
		void GoAttack(ACard* Card);
	UFUNCTION(BlueprintCallable)
		void UpdatePosition(ACard* Card, float Value);
	UFUNCTION(BlueprintCallable)
		void FinishAttack();
	void CheckTriple(ACard* Card);
	void Triple(FName Name);
	void DestroyCard(ACard* Card);

private:
	void SwitchPanel();
	void SettleBattle();
	void SetCurAttack(int32 &Index);
	int SelectTarget(TArray<ACard*> CardList);
	void GainCard(ACard* Card);
	void LoseCard(ACard* Card);
	void CombineProp(TArray<ACard*> Cards, ACard* GoldCard);
};