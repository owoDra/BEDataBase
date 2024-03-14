// Copyright (C) 2024 owoDra

#include "BEDataBaseSubsystem.h"

#include "Type/BEEquipDataBaseEntry.h"
#include "BEDataBaseDeveloperSettings.h"

#include "Engine/DataTable.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(BEDataBaseSubsystem)


// Initialization

void UBEDataBaseSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	LoadDefaultEquipmentDataTable();
}


float UBEDataBaseSubsystem::GetEquipmentParameter(const FName& Key, const FGameplayTag& DataTag, float DefaultValue) const
{
	if (Key.IsNone() || !DataTag.IsValid())
	{
		return DefaultValue;
	}

	FBEEquipDataBaseEntry* Entry{ nullptr };

	// オンラインサービスから取得したデータテーブルが存在する場合はそちらから参照する

	if (HasOnlineEquipmentDataTable())
	{
		Entry = OnlineEquipmentDataTable->FindRow<FBEEquipDataBaseEntry>(Key, TEXT("Get Entry From Online Equip Data Table"));
	}

	// オンラインさーぶすから取得できなかった場合はデフォルトのデータテーブルを参照する

	if (!Entry && DefaultEquipmentDataTable)
	{
		Entry = DefaultEquipmentDataTable->FindRow<FBEEquipDataBaseEntry>(Key, TEXT("Get Entry From Default Equip Data Table"));
	}

	// エントリーが見つかったらパラメーターを取得する

	if (Entry)
	{
		if (auto* FoundValue{ Entry->Parameters.Find(DataTag) })
		{
			return *FoundValue;
		}
	}

	return DefaultValue;
}

bool UBEDataBaseSubsystem::BuildOnlineEquipmentDataTable(const TArray<uint8> InBytesData)
{
	if (InBytesData.IsEmpty())
	{
		return false;
	}

	// Bytes データを JsonString に変換してテーブルを作成

	FString Json;
	FFileHelper::BufferToString(Json, InBytesData.GetData(), InBytesData.Num());

	auto* NewDataTable{ NewObject<UDataTable>(GetTransientPackage()) };
	NewDataTable->RowStruct = FBEEquipDataBaseEntry::StaticStruct();
	const auto Probrem{ NewDataTable->CreateTableFromJSONString(Json) };

	// 作成に問題がある場合は中断

	if (!Probrem.IsEmpty())
	{
		UE_LOG(LogTemp, Log, TEXT("Probrems: %s"), *FString::Join(Probrem, TEXT("; ")));
		UE_LOG(LogTemp, Log, TEXT("Json: %s"), *Json);

		return false;
	}

	// 既にテーブルが作成されている場合は破棄する

	if(OnlineEquipmentDataTable)
	{
		OnlineEquipmentDataTable->MarkAsGarbage();

		OnlineEquipmentDataTable = nullptr;
	}

	OnlineEquipmentDataTable = NewDataTable;

	return true;
}

bool UBEDataBaseSubsystem::HasOnlineEquipmentDataTable() const
{
	return IsValid(OnlineEquipmentDataTable);
}

void UBEDataBaseSubsystem::LoadDefaultEquipmentDataTable()
{
	const auto* DevSettings{ GetDefault<UBEDataBaseDeveloperSettings>() };

	DefaultEquipmentDataTable = Cast<UDataTable>(DevSettings->DefaultEquipmentDataTable.TryLoad());
}
