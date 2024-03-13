// Copyright (C) 2024 owoDra

#pragma once

#include "Engine/DeveloperSettings.h"

#include "BEDataBaseDeveloperSettings.generated.h"


/**
 * Settings for a Game framework.
 */
UCLASS(Config = "Game", Defaultconfig, meta = (DisplayName = "DataBase"))
class BEDATABASE_API UBEDataBaseDeveloperSettings : public UDeveloperSettings
{
public:
	GENERATED_BODY()
public:
	UBEDataBaseDeveloperSettings();


public:
	//
	// オンラインからデータテーブルを取得するのに使用するファイル名
	//
	UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category = "Equipment")
	FString EquipmentDataTableFileName{ TEXT("EquipmentDataTable") };

	//
	// オンラインからデータテーブルを取得できなかった場合に参照されるデフォルトのデータテーブル
	//
	UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category = "Equipment", meta = (AllowedClasses = "/Script/Engine.DataTable", RowType = "BEEquipDataBaseEntry"))
	FSoftObjectPath DefaultEquipmentDataTable;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Data Base")
	static FString GetEquipmentDataTableFileName() { return GetDefault<UBEDataBaseDeveloperSettings>()->EquipmentDataTableFileName; }

};

