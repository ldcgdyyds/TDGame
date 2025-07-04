// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "MainPanel.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMainPanel : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
		UButton* BtnStart;
	UPROPERTY(meta=(BindWidget))
	    UButton* BtnQuit;
};
