#include "PreCompile.h"
#include "Camp.h"
#include "Block.h"
#include "MapObject.h"
#include <EngineCore/DefaultSceneComponent.h>

ACamp::ACamp() 
{

}

ACamp::~ACamp() 
{
}

void ACamp::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Camp_Back1.png");
	Renderer->SetAutoSize(1.f, true);
}

void ACamp::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ACamp::AddObjectInit()
{
	{
		ABlock* MapObject = dynamic_cast<ABlock*>(AddMapObject(1, 1, EMapObject::CampBlock1).get());
		MapObject->SetPossessItem(EItemType::ItemBubble);
	}

	{
		ABlock* MapObject = dynamic_cast<ABlock*>(AddMapObject(3, 1, EMapObject::CampBlock1).get());
		MapObject->SetPossessItem(EItemType::ItemBubble);
	}
	
	AddMapObject(1, 3, EMapObject::CampBlock1);
	AddMapObject(3, 3, EMapObject::CampBlock1);

	AddMapObject(6, 6, EMapObject::CampMoveBlock1);
	AddMapObject(9, 6, EMapObject::CampMoveBlock1);
	AddMapObject(6, 9, EMapObject::CampMoveBlock1);
	AddMapObject(9, 9, EMapObject::CampMoveBlock1);

	AddMapObject(1, 6, EMapObject::CampHPBlock);
	AddMapObject(3, 6, EMapObject::CampHPBlock);
	AddMapObject(1, 9, EMapObject::CampHPBlock);
	AddMapObject(3, 9, EMapObject::CampHPBlock);

	AddMapObject(9, 1, EMapObject::TownBush);
	AddMapObject(10, 1, EMapObject::TownBush);

	/*{
		AddMapObject(0, 0, EMapObject::CampBlock2);
		AddMapObject(0, 2, EMapObject::CampBlock1);
		AddMapObject(0, 4, EMapObject::CampBlock1);
		AddMapObject(0, 6, EMapObject::TownBush);
		AddMapObject(0, 8, EMapObject::TownBush);
		AddMapObject(0, 10, EMapObject::CampBlock2);
		AddMapObject(0, 12, EMapObject::CampBlock2);
		AddMapObject(0, 14, EMapObject::CampBlock1);

		AddMapObject(1, 0, EMapObject::CampMoveBlock1);
		AddMapObject(1, 4, EMapObject::CampBlock3);
		AddMapObject(1, 5, EMapObject::CampBlock1);
		AddMapObject(1, 6, EMapObject::TownBush);
		AddMapObject(1, 8, EMapObject::TownBush);
		AddMapObject(1, 9, EMapObject::CampBlock2);
		AddMapObject(1, 10, EMapObject::CampBlock3);
		AddMapObject(1, 14, EMapObject::CampMoveBlock1);
		
		AddMapObject(2, 0, EMapObject::CampBlock2);
		AddMapObject(2, 2, EMapObject::CampBlock1);
		AddMapObject(2, 3, EMapObject::CampBlock3);
		AddMapObject(2, 5, EMapObject::CampHPBlock);
		AddMapObject(2, 6, EMapObject::CampBlock1);
		AddMapObject(2, 8, EMapObject::CampBlock2);
		AddMapObject(2, 9, EMapObject::CampHPBlock);
		AddMapObject(2, 11, EMapObject::CampBlock3);
		AddMapObject(2, 12, EMapObject::CampBlock2);
		AddMapObject(2, 14, EMapObject::CampBlock1);

		AddMapObject(3, 0, EMapObject::CampBlock1);
		AddMapObject(3, 1, EMapObject::CampBlock1);
		AddMapObject(3, 4, EMapObject::CampMoveBlock1);
		AddMapObject(3, 5, EMapObject::CampBlock1);
		AddMapObject(3, 6, EMapObject::TownBush);
		AddMapObject(3, 8, EMapObject::TownBush);
		AddMapObject(3, 9, EMapObject::CampBlock2);
		AddMapObject(3, 10, EMapObject::CampMoveBlock1);
		AddMapObject(3, 13, EMapObject::CampBlock2);
		AddMapObject(3, 14, EMapObject::CampBlock2);
		
		AddMapObject(4, 0, EMapObject::CampMoveBlock1);
		AddMapObject(4, 1, EMapObject::TownBush);
	}*/

}

