// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CardData.generated.h"

class UTexture2D;

UENUM(BlueprintType)
enum class ECardState : uint8
{
	Shop,
	Hand,
	Field,
	Battle,
	Pool
};

USTRUCT(BlueprintType)
struct FCardInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
		FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
		FString Ability;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
		int32 Star;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
		int32 Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CardInfo")
		int32 Health;
};