// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "CardUI.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UCardUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void InitializeCard(int32 Star, UTexture2D* Icon, int32 Attack, int32 Health, bool Gold);
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateLock(bool Lock);
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateCard(bool Battle);
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateInjury(int32 Health);
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateAttack(int32 Attack);
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateHealth(int32 Health);
	UPROPERTY(meta=(BindWidget))
		UButton* CardBtn;
};
