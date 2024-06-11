// Copyright Epic Games, Inc. All Rights Reserved.

#include "ScriptPackageHelperBPLibrary.h"

#include "BuildSettings.h"
#include "Editor.h"
#include "GameMapsSettings.h"
#include "GeneralEngineSettings.h"
#include "GeneralProjectSettings.h"
#include "IDetailTreeNode.h"
#include "ScriptPackageHelper.h"
#include "Core/Public/Misc/ConfigCacheIni.h"
#include "Editor/EditorPerProjectUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/FileHelper.h"
#include "Settings/ProjectPackagingSettings.h"

UScriptPackageHelperBPLibrary::UScriptPackageHelperBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}
UConfigObject* UScriptPackageHelperBPLibrary::GetConfigObj()
{
	UConfigObject* NewConfigObj = NewObject<UConfigObject>();
	
	return NewConfigObj;
}
FString UScriptPackageHelperBPLibrary::GetGameIniPath()
{
	return  FPaths::ProjectConfigDir() + FString("DefaultGame.ini");
}
FString UScriptPackageHelperBPLibrary::GetEngineIniPath()
{
	return   FPaths::ProjectConfigDir() + FString("DefaultEngine.ini");;
}

void UScriptPackageHelperBPLibrary::TestFunc()
{
	UE_LOG(LogTemp, Warning, TEXT("TestFunc"));
}

FString UScriptPackageHelperBPLibrary::GetStringValue(const FString& ConfigPath,const FString& Section,const FString& Key)
{
	FConfigFile GameConfig;
	GameConfig.Read(ConfigPath);
	FString Value;
	GameConfig.GetString(*Section,*Key,Value);

	return Value;
}

void UScriptPackageHelperBPLibrary::SetStringValue(const FString& ConfigPath,const FString& Section,const FString& Key,FString Value)
{
	FConfigFile GameConfig;
	GameConfig.Read(ConfigPath);
	GameConfig.SetString(*Section,*Key,*Value);

	GameConfig.Write(ConfigPath);
}

void UScriptPackageHelperBPLibrary::ClearArrayItems(const FString&  ConfigPath,const FString& Section,const FString& Key)
{

	FString ArrayKey = Key;
	if (!Key.StartsWith(TEXT("+")))
	{
		ArrayKey = FString("+")+ Key;
	}
	TArray<FString> NewArray;
	FConfigFile ConfigFile;
	FString gameConfigPath = FPaths::ProjectConfigDir() + TEXT("DefaultGame.ini");
	ConfigFile.Read(gameConfigPath);
	ConfigFile.SetArray(*Section,*ArrayKey,NewArray );
	ConfigFile.Write(gameConfigPath);

}

void UScriptPackageHelperBPLibrary::SetStringArray(const FString&  ConfigPath,const FString& Section,const FString& Key,TArray<FString> ItemArray)
{
	FString ArrayKey = Key;
	if (!Key.StartsWith(TEXT("+")))
	{
		ArrayKey = FString("+")+ Key;
	}
	
	FConfigFile ConfigFile;
	ConfigFile.Read(ConfigPath);
	ConfigFile.SetArray(*Section,*ArrayKey,ItemArray );
	ConfigFile.Write(ConfigPath);
	
}
TArray<FString> UScriptPackageHelperBPLibrary::GetArrayItems(const FString&  ConfigPath,const FString& Section,const FString& Key)
{
	TArray<FString> ItemArray;
	GConfig->GetArray(*Section,*Key,ItemArray,ConfigPath);
	
	 UE_LOG(LogTemp,Log,TEXT("GetArrayItems: ConfigPath: %s Section %s Key %s bAreFileOperationsDisabled %d"),*ConfigPath,*Section,*Key,GConfig->AreFileOperationsDisabled());
	for (int i = 0 ; i < ItemArray.Num(); i++)
	{
		UE_LOG(LogTemp,Log,TEXT("GetArrayItems: GetString: %s"),*(ItemArray[i]));
	}
	
	return ItemArray;
}
void UScriptPackageHelperBPLibrary::AddArrayItem(const FString&  ConfigPath,const FString& Section,const FString& Key,FString Item)
{
	FString ArrayKey = Key;
	if (!Key.StartsWith(TEXT("+")))
	{
		ArrayKey = FString("+")+ Key;
	}

	TArray<FString> ItemArray;
	FConfigFile ConfigFile;
	ConfigFile.Read(ConfigPath);
	ConfigFile.GetArray(*Section,*ArrayKey,ItemArray);
	ItemArray.AddUnique(Item);
	ConfigFile.SetArray(*Section,*ArrayKey,ItemArray );
	ConfigFile.Write(ConfigPath);
	
}