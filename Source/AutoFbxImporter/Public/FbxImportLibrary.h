// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FbxImportLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AUTOFBXIMPORTER_API UFbxImportLibrary : public UObject
{
	GENERATED_BODY()
	
public:

	UFbxImportLibrary(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = FbxImportLibrary)
	static UObject* ImportFbxFile(const FString& FbxFilePath, const FString DestinationPath);

	
	
	
};
