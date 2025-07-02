// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LuckMgr.generated.h"

class UDataTable;
class ULuckUI;

UCLASS()
class MYGAME_API ALuckMgr : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALuckMgr();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="DataTable")
		UDataTable* LuckCardDataTable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
		ULuckUI* LuckUI;
	TArray<FName> LuckCardNames;
	UFUNCTION(BlueprintCallable)
		void SelectLevel();
	UFUNCTION(BlueprintCallable)
		void StartGame();
	UFUNCTION(BlueprintCallable)
		void BackToMain();
	UFUNCTION(BlueprintCallable)
		void ConfirmInfo();
};
