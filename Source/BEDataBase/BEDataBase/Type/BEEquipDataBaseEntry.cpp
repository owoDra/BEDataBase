// Copyright (C) 2024 owoDra

#include "BEEquipDataBaseEntry.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(BEEquipDataBaseEntry)


void FBEEquipDataBaseEntry::OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName)
{
	TMap<FGameplayTag, float> SortedMap;

	TArray<FGameplayTag> CurrentTags;
	Parameters.GenerateKeyArray(CurrentTags);
	
	auto Container{ FGameplayTagContainer::CreateFromArray(CurrentTags) };
	for (const auto& Tag : Container)
	{
		SortedMap.Emplace(Tag, Parameters.FindRef(Tag));
	}

	Parameters = SortedMap;
}
