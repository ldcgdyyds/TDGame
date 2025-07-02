// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelItem.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API ULevelItem : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void UpdateColor(bool Selected);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void UpdateValue(int32 Value);
	UPROPERTY(BlueprintReadWrite)
		bool IsSelected;
};
