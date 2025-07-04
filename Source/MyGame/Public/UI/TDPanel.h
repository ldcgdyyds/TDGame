// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDPanel.generated.h"

class UMainPanel;
class USelectPanel;

/**
 * 
 */
UCLASS()
class MYGAME_API UTDPanel : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
		void BackToMain();
	UFUNCTION(BlueprintImplementableEvent)
		void QuitGame();
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
		UMainPanel* MainPanel;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
		USelectPanel* SelectPanel;
};
