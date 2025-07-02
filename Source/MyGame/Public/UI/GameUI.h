// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "GameUI.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/*UFUNCTION(BlueprintImplementableEvent)
		void InitializeGame(int32 TurnTimes, int32 CurCoins, int32 Level, 
		int32 LevelUpCost, int32 RefreshCost, int32 LockCost, int32 Health);
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateTimer(int32 TurnTimes);
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateCoins(int32 CurCoins);
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateLevel(int32 Level);
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateLevelupcost(int32 LevelUpCost);
	UFUNCTION(BlueprintImplementableEvent)
		void UpdatePanel(bool Battle);
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateInjury(int32 Health);
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
		UButton* LevelUpBtn;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
		UButton* RefreshBtn;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
		UButton* LockBtn;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
		UButton* PanelBtn;*/
	UFUNCTION(BlueprintImplementableEvent)
		void ConfirmInfo();
	UPROPERTY(meta=(BindWidget))
		UButton* BtnConfirm;
};
