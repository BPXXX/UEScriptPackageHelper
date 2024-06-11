// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ConfigObject.generated.h"

/**
 * 
 */
UCLASS(Config=Game)
class SCRIPTPACKAGEHELPER_API UConfigObject : public UObject
{
	GENERATED_BODY()
public:
	
	UPROPERTY(config, EditAnywhere, Category=Packaging)
	FString TestString;
};
