// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardData.h"
#include "GameFramework/Actor.h"
#include "Card.generated.h"

class UWidgetComponent;
class UCardUI;
class UEventCenter;
class UCardPool;
class AGamePlayer;
class UAbility;

UCLASS()
class MYGAME_API ACard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MyWidgetComponent")
		UWidgetComponent* Widget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
		UCardUI* CardUI;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="EventCenter")
		UEventCenter* EventCenter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="CardPool")
		UCardPool* CardPool;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player")
		AGamePlayer* PlayerRef;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Icon")
		UTexture2D* Icon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ability")
		UAbility* Ability;
	FVector3d CardLocation;
	FString Id;FName Name;int32 Star, Attack, Health, AttackBase, HealthBase;bool bGold, bDead;
	ECardState CardState;
	FTimerHandle CardTimerHandle;
	UFUNCTION(BlueprintCallable)
		void BeTarget();
	UFUNCTION(BlueprintCallable)
		void StartDrag();
	UFUNCTION(BlueprintCallable)
		void EndDrag();
	void SetLocation();
	void InitializeCard(AGamePlayer* Player, FCardInfo* CardInfo, bool Gold);
	void TransCard();
	void TransMinion();
	void RandomMinion(FCardInfo* CardInfo, bool Gold);
	void CopyMinion(int32 PStar, UTexture2D* PIcon, int32 PAttack, int32 PHealth, bool Gold);
	void SettleDamage(ACard* Card);
	void BeOptions();
	void BeNormal();
	void OnStateUpdate(ECardState NewCardState);
	void OnPurchase();
	void OnSell();
	void OnPlay();
	void OnTurnEnd();
	void OnAttack(ACard* Card);
	void OnDestroy(ECardState NewCardState);

private:
	void CreateCard();
	void CreateMinion();
};
