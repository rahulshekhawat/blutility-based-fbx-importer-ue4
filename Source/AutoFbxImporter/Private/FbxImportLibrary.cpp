// Fill out your copyright notice in the Description page of Project Settings.

#include "FbxImportLibrary.h"

#include "Misc/Paths.h"
#include "PackageTools.h"
#include "Engine/StaticMesh.h"
#include "Engine/SkeletalMesh.h"
#include "Factories/FbxFactory.h"
#include "AssetToolsModule.h"
#include "AssetRegistryModule.h"

UFbxImportLibrary::UFbxImportLibrary(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{
}

UObject * UFbxImportLibrary::ImportFbxFile(const FString & FbxFilePath, const FString DestinationPath)
{
	UObject* ImportedObject = nullptr;
	UPackage* ModelPackage = nullptr;
	FString LogMessage;

	FbxFilePath.Replace(TEXT("\""), TEXT("/"));

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	UFbxFactory* FbxFactory = NewObject<UFbxFactory>();
	FbxFactory->AddToRoot();
	FbxFactory->EnableShowOption();

	FString FbxFileName = FPaths::GetBaseFilename(FbxFilePath);
	FString ModelPackageName = DestinationPath + FString("/") + FbxFileName;
	ModelPackageName = PackageTools::SanitizePackageName(ModelPackageName);

	if(FPackageName::DoesPackageExist(ModelPackageName))
	{
		ModelPackage = LoadPackage(nullptr, *ModelPackageName, LOAD_None);
		if(ModelPackage)
		{
			ModelPackage->FullyLoad();
		}

		LogMessage = ModelPackageName + FString(" already exists!");
		UE_LOG(LogTemp, Warning, TEXT("%s"), *LogMessage);
	}
	else
	{
		ModelPackage = CreatePackage(nullptr, *ModelPackageName);
		ModelPackage->FullyLoad();
	}

	bool bImportCancelled = false;
	ImportedObject = FbxFactory->ImportObject(UStaticMesh::StaticClass(),
	 			 							  ModelPackage, FName(*FbxFileName),
											  EObjectFlags::RF_Standalone | EObjectFlags::RF_Public,
											  FbxFilePath,
											  nullptr,
											  bImportCancelled);

	if (bImportCancelled)
	{
		if (ModelPackage)
		{
			// @todo clean up created package
			// ModelPackage->ConditionalBeginDestroy();
		}
	}

	// @todo save package

	FbxFactory->RemoveFromRoot();
	FbxFactory->ConditionalBeginDestroy();
	FbxFactory = nullptr;
	return ImportedObject;
}
