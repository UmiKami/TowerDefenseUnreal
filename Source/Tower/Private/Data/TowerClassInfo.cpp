// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Data/TowerClassInfo.h"

#if WITH_EDITOR
void UTowerClassInfo::PreEditChange(FProperty* PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);

	CachedTowerClassInformation = TowerClassInformation;
}

void UTowerClassInfo::SetGhostSkeletalMeshOnTowerMeshSet(struct FPropertyChangedChainEvent& PropertyChangedEvent,
                                                         const FName PropertyName)
{
	if (PropertyName != GET_MEMBER_NAME_CHECKED(FTowerClasDefaultInfo, SkeletalMeshComponentPerLevel)) return;
	if (!IsValid(GhostMaterialInstance)) return;


	const int32 ChangedIndex = PropertyChangedEvent.GetArrayIndex(TEXT("SkeletalMeshComponentPerLevel"));


	for (const auto& NewPair : TowerClassInformation)
	{
		const ETowerClass TowerClassKey = NewPair.Key;
		const FTowerClasDefaultInfo& NewInfo = NewPair.Value;

		const FTowerClasDefaultInfo* OldInfo = CachedTowerClassInformation.Find(TowerClassKey);

		if (!OldInfo)
		{
			UE_LOG(LogTemp, Warning, TEXT("New tower class entry added"));
			continue;
		}

		if (OldInfo->SkeletalMeshComponentPerLevel.Find(ChangedIndex + 1) != NewInfo.SkeletalMeshComponentPerLevel.Find(
			ChangedIndex + 1))
		{
			for (const auto& NewMeshPair : NewInfo.SkeletalMeshComponentPerLevel)
			{
				const int32 LevelKey = NewMeshPair.Key;

				USkeletalMesh* OriginalMesh = NewMeshPair.Value.Get();

				USkeletalMesh* NewMesh = DuplicateObject<USkeletalMesh>(
					OriginalMesh,
					this
				);

				const TObjectPtr<USkeletalMesh>* OldMeshPtr =
					OldInfo->SkeletalMeshComponentPerLevel.Find(LevelKey);

				const USkeletalMesh* OldMesh = OldMeshPtr ? OldMeshPtr->Get() : nullptr;

				if (OldMesh != NewMesh)
				{
					UE_LOG(LogTemp, Warning, TEXT("Mesh changed for TowerClass %s, Level %d"),
					       *StaticEnum<ETowerClass>()->GetNameStringByValue((int64)TowerClassKey),
					       LevelKey);

					if (!IsValid(NewMesh)) continue;

					NewMesh->SetMaterials({FSkeletalMaterial{GhostMaterialInstance}});

					TowerClassInformation[TowerClassKey]
						.SkeletalGhostMeshComponentPerLevel
						.Add(LevelKey, NewMesh);
				}
			}
		}
	}
}

void UTowerClassInfo::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	const FName PropertyName = PropertyChangedEvent.Property
		                           ? PropertyChangedEvent.Property->GetFName()
		                           : NAME_None;
	
	SetGhostSkeletalMeshOnTowerMeshSet(PropertyChangedEvent, PropertyName);
}
#endif
