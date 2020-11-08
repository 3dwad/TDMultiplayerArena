// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncLoadTest.h"

#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

void UAsyncLoadTest::TryAsyncLoad()
{
	// if (TestingMesh.Get())
	// 	GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Green, "Asset loaded");
	// else
	// 	GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Green, "Asset not loaded");



	
	//GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Red,FString::Printf(TEXT("Start loadin at %d"), FDateTime::Now().GetSecond()));
	// for (auto Element : TestingMeshes)
	// {
	// 	if (!Element.Get())
	// 		GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Red, "Asset not load");
	// }

	FStreamableManager& AssetLoader = UAssetManager::Get().GetStreamableManager();
	//FStreamableManager AssetLoader;
	//TArray<FSoftObjectPath> AssetsForLoad;
	for (auto Element : TestingMeshes)
	{
		auto AssetToLoad = Element.ToSoftObjectPath();
		AssetLoader.RequestAsyncLoad(AssetToLoad, FStreamableDelegate::CreateUObject(this, &UAsyncLoadTest::OnAssetLoad));
		//AssetsForLoad.Add(AssetToLoad);
	}

	//AssetLoader.RequestAsyncLoad(AssetsForLoad, FStreamableDelegate::CreateUObject(this, &UAsyncLoadTest::OnAssetLoad),	1, true);

	// for (auto Element : TestingMeshes)
	// {
	// 	if (Element.Get())
	// 		GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Green, "Asset already load");
	// }

//	GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Green, FString::Printf(TEXT("Start loadin at %d"), FDateTime::Now().GetSecond()));



	
// if (m_BodyPartsPtr != nullptr)
//      {
//          FStringAssetReference AssetToLoad;
//          AssetToLoad = m_BodyPartsPtr.ToStringReference();
//  
//          AssetLoader.RequestAsyncLoad(AssetToLoad, FStreamableDelegate::CreateUObject(this, &ACBaseUnitCharacter::LoadedAsstes), 1, true);
//      }
//  ...
//  }
//  
//      //Loaded assets callback - for me it is only 1 item so I left it as an empty implementation
//      void ACBaseUnitCharacter::LoadedAsstes()
//      {
//          if (m_BodyPartsPtr != nullptr)
//          {
//              if (m_BodyPartsPtr.IsValid())
//              {
//              }
//          }
//      }
//      
//      //The spawn itself!
//      ABaseBodyPartsActor* ACBaseUnitCharacter::SpawnParts(FTransform transform)
//      {
//          if (m_BodyPartsPtr.IsValid() && GetWorld())
//          {
//              return GetWorld()->SpawnActor<ABaseBodyPartsActor>(m_BodyPartsPtr.Get(), transform);
//          }
//          else
//          {
//              return nullptr;
//          }
//      }

	//
	// GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Red, "Start loading ");
	// if(auto some =TestingMesh.LoadSynchronous())
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Green, "Loading finish ");
	// }
	
	// FStreamableManager AssetLoader;
	//
	// AssetLoader.RequestAsyncLoad()
}

void UAsyncLoadTest::OnAssetLoad()
{
	//GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Yellow, "Must be loaded");
}
