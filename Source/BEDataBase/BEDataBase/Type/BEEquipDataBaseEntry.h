// Copyright (C) 2024 owoDra

#pragma once

#include "Engine/DataTable.h"

#include "GameplayTagContainer.h"

#include "BEEquipDataBaseEntry.generated.h"


/** 
 * �f�[�^�x�[�X�ɓo�^����(����)�����̏��
 */
USTRUCT(BlueprintType)
struct BEDATABASE_API FBEEquipDataBaseEntry : public FTableRowBase
{
	GENERATED_BODY()
public:
	FBEEquipDataBaseEntry() = default;

public:
	//
	// �f�[�^�̃L�[�ƂȂ� GameplayTag �ƒl�̃}�b�s���O���X�g
	//
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ForceInlineRow, Categories = "DataBase"))
	TMap<FGameplayTag, float> Parameters;

};
