// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDMgr.generated.h"

class UTDPanel;

UCLASS()
class MYGAME_API ATDMgr : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDMgr();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
		UTDPanel* TDPanel;
	UFUNCTION(BlueprintCallable)
		void StartGame();
	UFUNCTION(BlueprintCallable)
		void BackToMain();
	UFUNCTION(BlueprintCallable)
		void QuitGame();
};
