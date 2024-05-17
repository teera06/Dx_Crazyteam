#include "PreCompile.h"
#include "Bush.h"
#include "CAGameMode.h"
#include "BaseMap.h"
#include "Block.h"

ABush::ABush() 
{
}

ABush::~ABush() 
{
}

void ABush::SetPossessBlock(std::shared_ptr<AMapObject> _Block)
{
	PossessBlock = _Block;
	_Block->SetIsPossess(true);
	_Block->SetCurPos(GetCurPos());
}

void ABush::BeginPlay()
{
	Super::BeginPlay();
	
	SetType(EMapObjectType::Bush);

	WaterInteract = [=]
		{
			if (GetPossessBlock() == nullptr)
			{
				GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
			}
			else
			{
				PossessBlock->WaterInteract();
			}
		};

	PlayerInteract = [=]
		{
			if (GetPossessBlock() == nullptr)
			{
				return;
			}
			else
			{
				PossessBlock->PlayerInteract();
			}
		};
}

void ABush::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

