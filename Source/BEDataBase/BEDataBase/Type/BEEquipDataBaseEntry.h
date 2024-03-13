// Copyright (C) 2024 owoDra

#pragma once

#include "Engine/DataTable.h"

#include "GameplayTagContainer.h"

#include "BEEquipDataBaseEntry.generated.h"


/** 
 * データベースに登録する(した)装備の情報
 */
USTRUCT(BlueprintType)
struct BEDATABASE_API FBEEquipDataBaseEntry : public FTableRowBase
{
	GENERATED_BODY()
public:
	FBEEquipDataBaseEntry() = default;

public:
	//
	// データのキーとなる GameplayTag と値のマッピングリスト
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ForceInlineRow, Categories = "DataBase"))
	TMap<FGameplayTag, float> Parameters;

};
