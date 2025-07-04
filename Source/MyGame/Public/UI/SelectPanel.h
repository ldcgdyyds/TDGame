// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "SelectPanel.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API USelectPanel : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
		UButton* BtnBack;
};
