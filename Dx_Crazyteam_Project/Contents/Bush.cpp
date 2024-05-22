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
	if (_Block != nullptr)
	{
		_Block->SetIsPossessed(true);
		_Block->SetCurPos(GetCurPos());
		PossessBlock = _Block;
	}
	else
	{
		PossessBlock = nullptr;
	}
}

void ABush::BeginPlay()
{
	Super::BeginPlay();

	BreakSetOwner(this);
	MoveSetOwner(this);
	
	SetType(EMapObjectType::Bush);
	SetPossessItem(EItemType::None);
}

void ABush::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

