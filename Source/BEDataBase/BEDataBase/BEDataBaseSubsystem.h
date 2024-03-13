// Copyright (C) 2024 owoDra

#pragma once

#include "Subsystems/GameInstanceSubsystem.h"

#include "GameplayTagContainer.h"

#include "BEDataBaseSubsystem.generated.h"

class UDataTable;


/**
 * データベースを管理するサブシステム
 */
UCLASS(BlueprintType)
class BEDATABASE_API UBEDataBaseSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public:
    UBEDataBaseSubsystem() {}

    ///////////////////////////////////////////////////////////////////////
    // Initialization
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    
    ///////////////////////////////////////////////////////////////////////
    // Equipment Data Table
protected:
	UPROPERTY(Transient)
    TObjectPtr<const UDataTable> DefaultEquipmentDataTable;

	UPROPERTY(Transient)
    TObjectPtr<UDataTable> OnlineEquipmentDataTable;

public:
	UFUNCTION(BlueprintCallable, Category = "Data Base", meta = (AdvancedDisplay = "DefaultValue"))
    virtual float GetEquipmentParameter(const FPrimaryAssetId& AssetId, const FGameplayTag& DataTag, float DefaultValue = 0.0f) const;

	UFUNCTION(BlueprintCallable, Category = "Data Base")
    virtual bool BuildOnlineEquipmentDataTable(const TArray<uint8> InBytesData);

    UFUNCTION(BlueprintCallable, Category = "Data Base", meta = (ExpandBoolAsExecs = "ReturnValue"))
    virtual bool HasOnlineEquipmentDataTable() const;

    UFUNCTION(BlueprintCallable, BlueprintPure = "false", Category = "Data Base")
    virtual const UDataTable* GetDefaultEquipmentDataTable() const { return DefaultEquipmentDataTable; }

    UFUNCTION(BlueprintCallable, BlueprintPure = "false", Category = "Data Base")
    virtual const UDataTable* GetOnlineEquipmentDataTable() const { return OnlineEquipmentDataTable; }

protected:
    virtual void LoadDefaultEquipmentDataTable();

};
