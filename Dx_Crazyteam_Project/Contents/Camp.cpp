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

}

