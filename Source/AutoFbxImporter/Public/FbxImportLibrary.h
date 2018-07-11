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

	/**
	 * Import a single fbx File inside Unreal Engine
	 * @param FbxFilePath The path of fbx file that needs to be imported
	 * @param DestinationPath Path of editor directory where fbx file has to be
	 * imported (e.g. /Game/EOD/Model)
	*/
	UFUNCTION(BlueprintCallable, Category = FbxImportLibrary)
	static UObject* ImportFbxFile(const FString& FbxFilePath, const FString DestinationPath);
	
};
