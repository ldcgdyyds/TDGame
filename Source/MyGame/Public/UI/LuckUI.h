// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LuckUI.generated.h"

class UMainPanel;
class USelectPanel;
class UGameUI;

/**
 * 
 */
UCLASS()
class MYGAME_API ULuckUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void SelectLevel();
	UFUNCTION(BlueprintImplementableEvent)
		void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
		void BackToMain();
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
		UMainPanel* LuckMainUI;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
		USelectPanel* LuckLevelUI;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
		UGameUI* LuckGameUI;
};
