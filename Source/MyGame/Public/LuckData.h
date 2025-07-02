// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LuckData.generated.h"

class UTexture2D;

UENUM(BlueprintType)
enum class ELuckRarity : uint8
{
	Common,
	Rare,
	SuperRare,
	Legend
};

USTRUCT(BlueprintType)
struct FLuckCardInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LuckCardInfo")
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LuckCardInfo")
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LuckCardInfo")
		ELuckRarity Rarity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LuckCardInfo")
		int32 Benefit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LuckCardInfo")
		FString Ability;
};
