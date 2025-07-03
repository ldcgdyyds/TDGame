// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDPanel.generated.h"

class UMainPanel;

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
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
		UMainPanel* MainPanel;
};
