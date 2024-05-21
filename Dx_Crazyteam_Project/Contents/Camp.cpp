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
		AddMapObject(4, 2, EMapObject::TownBush);
		AddMapObject(4, 3, EMapObject::CampBlock1);
		AddMapObject(4, 5, EMapObject::CampMoveBlock1);
		AddMapObject(4, 6, EMapObject::CampBlock1);
		AddMapObject(4, 8, EMapObject::CampBlock2);
		AddMapObject(4, 9, EMapObject::CampMoveBlock1);
		AddMapObject(4, 10, EMapObject::TownBush);
		AddMapObject(4, 11, EMapObject::CampBlock2);
		AddMapObject(4, 12, EMapObject::TownBush);
		AddMapObject(4, 14, EMapObject::CampMoveBlock1);

		{
			std::shared_ptr<ABlock> hpblock1 = std::dynamic_pointer_cast<ABlock>(AddMapObject(5, 0, EMapObject::CampHPBlock));

			hpblock1->SetHp(2);
		}
		AddMapObject(5, 1, EMapObject::CampMoveBlock1);
		AddMapObject(5, 5, EMapObject::CampBlock1);
		AddMapObject(5, 6, EMapObject::CampMoveBlock1);
		AddMapObject(5, 8, EMapObject::CampMoveBlock1);
		AddMapObject(5, 9, EMapObject::CampBlock2);
		AddMapObject(5, 10, EMapObject::TownBush);
		AddMapObject(5, 13, EMapObject::CampMoveBlock1);
		{
			std::shared_ptr<ABlock> hpblock1 = std::dynamic_pointer_cast<ABlock>(AddMapObject(5, 14, EMapObject::CampHPBlock));

			hpblock1->SetHp(2);
		}

		AddMapObject(6, 0, EMapObject::CampBlock1);
		AddMapObject(6, 1, EMapObject::CampBlock3);
		AddMapObject(6, 2, EMapObject::TownBush);
		AddMapObject(6, 3, EMapObject::CampBlock1);
		AddMapObject(6, 4, EMapObject::TownBush);
		AddMapObject(6, 5, EMapObject::CampMoveBlock1);
		AddMapObject(6, 6, EMapObject::CampBlock1);
		AddMapObject(6, 8, EMapObject::CampBlock2);
		AddMapObject(6, 9, EMapObject::CampMoveBlock1);
		AddMapObject(6, 10, EMapObject::TownBush);
		AddMapObject(6, 11, EMapObject::CampBlock2);
		AddMapObject(6, 12, EMapObject::TownBush);
		AddMapObject(6, 13, EMapObject::CampBlock3);
		AddMapObject(6, 14, EMapObject::CampBlock2);

		AddMapObject(7, 0, EMapObject::CampBlock1);
		AddMapObject(7, 4, EMapObject::CampMoveBlock1);
		AddMapObject(7, 5, EMapObject::CampBlock1);
		AddMapObject(7, 6, EMapObject::TownBush);
		AddMapObject(7, 8, EMapObject::TownBush);
		AddMapObject(7, 9, EMapObject::CampBlock2);
		AddMapObject(7, 10, EMapObject::CampMoveBlock1);
		AddMapObject(7, 14, EMapObject::CampBlock2);

		{
			std::shared_ptr<ABlock> hpblock1 = std::dynamic_pointer_cast<ABlock>(AddMapObject(8, 0, EMapObject::CampHPBlock));

			hpblock1->SetHp(2);
		}
		AddMapObject(8, 1, EMapObject::CampBlock1);
		AddMapObject(8, 2, EMapObject::TownBush);
		AddMapObject(8, 3, EMapObject::TownBush);
		AddMapObject(8, 5, EMapObject::CampBlock1);
		AddMapObject(8, 6, EMapObject::TownBush);
		AddMapObject(8, 8, EMapObject::TownBush);
		AddMapObject(8, 9, EMapObject::CampBlock2);
		AddMapObject(8, 11, EMapObject::TownBush);
		AddMapObject(8, 12, EMapObject::TownBush);
		AddMapObject(8, 13, EMapObject::CampBlock2);
		{
			std::shared_ptr<ABlock> hpblock1 = std::dynamic_pointer_cast<ABlock>(AddMapObject(8, 14, EMapObject::CampHPBlock));

			hpblock1->SetHp(2);
		}

		AddMapObject(9, 0, EMapObject::CampMoveBlock1);
		AddMapObject(9, 1, EMapObject::CampMoveBlock1);
		AddMapObject(9, 2, EMapObject::CampMoveBlock1);
		AddMapObject(9, 3, EMapObject::CampBlock1);
		AddMapObject(9, 5, EMapObject::CampBlock1);
		AddMapObject(9, 6, EMapObject::TownBush);
		AddMapObject(9, 8, EMapObject::TownBush);
		AddMapObject(9, 9, EMapObject::CampBlock2);
		AddMapObject(9, 11, EMapObject::CampBlock2);
		AddMapObject(9, 12, EMapObject::CampMoveBlock1);
		AddMapObject(9, 13, EMapObject::CampMoveBlock1);
		AddMapObject(9, 14, EMapObject::CampMoveBlock1);

		AddMapObject(10, 0, EMapObject::CampBlock1);
		AddMapObject(10, 1, EMapObject::CampBlock1);
		AddMapObject(10, 2, EMapObject::CampBlock1);
		AddMapObject(10, 3, EMapObject::CampBlock3);
		AddMapObject(10, 5, EMapObject::CampBlock1);
		AddMapObject(10, 6, EMapObject::TownBush);
		AddMapObject(10, 8, EMapObject::TownBush);
		AddMapObject(10, 9, EMapObject::CampBlock2);
		AddMapObject(10, 11, EMapObject::CampBlock3);
		AddMapObject(10, 12, EMapObject::CampBlock2);
		AddMapObject(10, 13, EMapObject::CampBlock2);
		AddMapObject(10, 14, EMapObject::CampBlock2);

		AddMapObject(11, 0, EMapObject::CampMoveBlock1);
		AddMapObject(11, 4, EMapObject::CampBlock3);
		AddMapObject(11, 5, EMapObject::CampHPBlock);
		AddMapObject(11, 6, EMapObject::CampBlock1);
		AddMapObject(11, 8, EMapObject::CampBlock2);
		AddMapObject(11, 9, EMapObject::CampHPBlock);
		AddMapObject(11, 10, EMapObject::CampBlock3);
		AddMapObject(11, 14, EMapObject::CampMoveBlock1);

		AddMapObject(12, 2, EMapObject::CampBlock1);
		AddMapObject(12, 3, EMapObject::CampBlock1);
		AddMapObject(12, 4, EMapObject::CampMoveBlock1);
		AddMapObject(12, 5, EMapObject::CampBlock1);
		AddMapObject(12, 6, EMapObject::TownBush);
		AddMapObject(12, 8, EMapObject::TownBush);
		AddMapObject(12, 9, EMapObject::CampBlock2);
		AddMapObject(12, 10, EMapObject::CampMoveBlock1);
		AddMapObject(12, 11, EMapObject::CampBlock1);
		AddMapObject(12, 12, EMapObject::CampBlock2);
	}

}

