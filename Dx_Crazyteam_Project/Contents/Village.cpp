#include "PreCompile.h"
#include "Village.h"
#include <EngineCore/DefaultSceneComponent.h>

AVillage::AVillage()
{

}

AVillage::~AVillage()
{
}


void AVillage::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Village_Back2.png");
	Renderer->SetAutoSize(1.f, true);
}

void AVillage::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AVillage::AddObjectInit()
{
	AddMapObject(0, 1, EMapObject::VillageBlock2);
	AddMapObject(0, 2, EMapObject::VillageBlock1);
	AddMapObject(0, 3, EMapObject::VillageBlock2);
	AddMapObject(0, 4, EMapObject::VillageBlock1);
	AddMapObject(0, 5, EMapObject::TownBush);
	AddMapObject(0, 8, EMapObject::VillageMoveBlock);
	AddMapObject(0, 9, EMapObject::TownBush);
	AddMapObject(0, 10, EMapObject::VillageYellowHouse);
	AddMapObject(0, 11, EMapObject::VillageBlock1);
	AddMapObject(0, 12, EMapObject::VillageYellowHouse);
	AddMapObject(0, 14, EMapObject::VillageYellowHouse);

	AddMapObject(1, 1, EMapObject::VillageRedHouse);
	AddMapObject(1, 2, EMapObject::VillageMoveBlock);
	AddMapObject(1, 3, EMapObject::VillageRedHouse);
	AddMapObject(1, 4, EMapObject::VillageMoveBlock);
	AddMapObject(1, 5, EMapObject::VillageTree);
	AddMapObject(1, 6, EMapObject::VillageMoveBlock);
	AddMapObject(1, 9, EMapObject::VillageTree);
	AddMapObject(1, 10, EMapObject::VillageBlock1);
	AddMapObject(1, 11, EMapObject::VillageBlock2);

	AddMapObject(2, 2, EMapObject::VillageBlock2);
	AddMapObject(2, 3, EMapObject::VillageBlock1);
	AddMapObject(2, 4, EMapObject::VillageBlock2);
	AddMapObject(2, 5, EMapObject::TownBush);
	AddMapObject(2, 7, EMapObject::VillageMoveBlock);
	AddMapObject(2, 8, EMapObject::VillageMoveBlock);
	AddMapObject(2, 9, EMapObject::TownBush);
	AddMapObject(2, 10, EMapObject::VillageYellowHouse);
	AddMapObject(2, 11, EMapObject::VillageMoveBlock);
	AddMapObject(2, 12, EMapObject::VillageYellowHouse);
	AddMapObject(2, 13, EMapObject::VillageMoveBlock);
	AddMapObject(2, 14, EMapObject::VillageYellowHouse);

	AddMapObject(3, 0, EMapObject::VillageMoveBlock);
	AddMapObject(3, 1, EMapObject::VillageRedHouse);
	AddMapObject(3, 2, EMapObject::VillageMoveBlock);
	AddMapObject(3, 3, EMapObject::VillageRedHouse);
	AddMapObject(3, 4, EMapObject::VillageMoveBlock);
	AddMapObject(3, 5, EMapObject::VillageTree);
	AddMapObject(3, 6, EMapObject::VillageMoveBlock);
	AddMapObject(3, 9, EMapObject::VillageTree);
	AddMapObject(3, 10, EMapObject::VillageBlock2);
	AddMapObject(3, 11, EMapObject::VillageBlock1);
	AddMapObject(3, 12, EMapObject::VillageBlock2);
	AddMapObject(3, 13, EMapObject::VillageBlock1);
	AddMapObject(3, 14, EMapObject::VillageBlock2);

	AddMapObject(4, 0, EMapObject::VillageBlock1);
	AddMapObject(4, 1, EMapObject::VillageBlock2);
	AddMapObject(4, 2, EMapObject::VillageBlock1);
	AddMapObject(4, 3, EMapObject::VillageBlock2);
	AddMapObject(4, 4, EMapObject::VillageBlock1);
	AddMapObject(4, 5, EMapObject::TownBush);
	AddMapObject(4, 8, EMapObject::VillageMoveBlock);
	AddMapObject(4, 9, EMapObject::TownBush);
	AddMapObject(4, 10, EMapObject::VillageYellowHouse);
	AddMapObject(4, 11, EMapObject::VillageMoveBlock);
	AddMapObject(4, 12, EMapObject::VillageYellowHouse);
	AddMapObject(4, 13, EMapObject::VillageMoveBlock);
	AddMapObject(4, 14, EMapObject::VillageYellowHouse);

	AddMapObject(5, 0, EMapObject::VillageBlock2);
	AddMapObject(5, 1, EMapObject::VillageRedHouse);
	AddMapObject(5, 2, EMapObject::VillageBlock2);
	AddMapObject(5, 3, EMapObject::VillageRedHouse);
	AddMapObject(5, 4, EMapObject::VillageBlock2);
	AddMapObject(5, 5, EMapObject::VillageTree);
	AddMapObject(5, 6, EMapObject::VillageMoveBlock);
	AddMapObject(5, 7, EMapObject::VillageMoveBlock);
	AddMapObject(5, 10, EMapObject::VillageBlock1);
	AddMapObject(5, 11, EMapObject::VillageBlock2);
	AddMapObject(5, 12, EMapObject::VillageBlock1);
	AddMapObject(5, 13, EMapObject::VillageBlock2);
	AddMapObject(5, 14, EMapObject::VillageBlock1);

	AddMapObject(6, 0, EMapObject::VillageTree);
	AddMapObject(6, 1, EMapObject::TownBush);
	AddMapObject(6, 2, EMapObject::VillageTree);
	AddMapObject(6, 3, EMapObject::TownBush);
	AddMapObject(6, 4, EMapObject::VillageTree);
	AddMapObject(6, 5, EMapObject::TownBush);
	AddMapObject(6, 8, EMapObject::VillageMoveBlock);
	AddMapObject(6, 9, EMapObject::TownBush);
	AddMapObject(6, 10, EMapObject::VillageTree);
	AddMapObject(6, 11, EMapObject::TownBush);
	AddMapObject(6, 12, EMapObject::VillageTree);
	AddMapObject(6, 13, EMapObject::TownBush);
	AddMapObject(6, 14, EMapObject::VillageTree);

	AddMapObject(7, 0, EMapObject::VillageBlock1);
	AddMapObject(7, 1, EMapObject::VillageBlock2);
	AddMapObject(7, 2, EMapObject::VillageBlock1);
	AddMapObject(7, 3, EMapObject::VillageBlock2);
	AddMapObject(7, 4, EMapObject::VillageBlock1);
	AddMapObject(7, 6, EMapObject::VillageMoveBlock);
	AddMapObject(7, 9, EMapObject::VillageTree);
	AddMapObject(7, 10, EMapObject::VillageBlock1);
	AddMapObject(7, 11, EMapObject::VillageRedHouse);
	AddMapObject(7, 12, EMapObject::VillageBlock1);
	AddMapObject(7, 13, EMapObject::VillageRedHouse);
	AddMapObject(7, 14, EMapObject::VillageBlock1);

	AddMapObject(8, 0, EMapObject::VillageBlueHouse);
	AddMapObject(8, 1, EMapObject::VillageMoveBlock);
	AddMapObject(8, 2, EMapObject::VillageBlueHouse);
	AddMapObject(8, 3, EMapObject::VillageMoveBlock);
	AddMapObject(8, 4, EMapObject::VillageBlueHouse);
	AddMapObject(8, 5, EMapObject::TownBush);
	AddMapObject(8, 7, EMapObject::VillageMoveBlock);
	AddMapObject(8, 8, EMapObject::VillageMoveBlock);
	AddMapObject(8, 9, EMapObject::TownBush);
	AddMapObject(8, 10, EMapObject::VillageBlock2);
	AddMapObject(8, 11, EMapObject::VillageBlock1);
	AddMapObject(8, 12, EMapObject::VillageBlock2);
	AddMapObject(8, 13, EMapObject::VillageBlock1);
	AddMapObject(8, 14, EMapObject::VillageBlock2);

	AddMapObject(9, 0, EMapObject::VillageBlock2);
	AddMapObject(9, 1, EMapObject::VillageBlock1);
	AddMapObject(9, 2, EMapObject::VillageBlock2);
	AddMapObject(9, 3, EMapObject::VillageBlock1);
	AddMapObject(9, 4, EMapObject::VillageBlock2);
	AddMapObject(9, 5, EMapObject::VillageTree);
	AddMapObject(9, 6, EMapObject::VillageMoveBlock);
	AddMapObject(9, 9, EMapObject::VillageTree);
	AddMapObject(9, 10, EMapObject::VillageMoveBlock);
	AddMapObject(9, 11, EMapObject::VillageRedHouse);
	AddMapObject(9, 12, EMapObject::VillageMoveBlock);
	AddMapObject(9, 13, EMapObject::VillageRedHouse);
	AddMapObject(9, 14, EMapObject::VillageMoveBlock);

	AddMapObject(10, 0, EMapObject::VillageBlueHouse);
	AddMapObject(10, 2, EMapObject::VillageBlueHouse);
	AddMapObject(10, 3, EMapObject::VillageMoveBlock);
	AddMapObject(10, 4, EMapObject::VillageBlueHouse);
	AddMapObject(10, 5, EMapObject::TownBush);
	AddMapObject(10, 8, EMapObject::VillageMoveBlock);
	AddMapObject(10, 9, EMapObject::TownBush);
	AddMapObject(10, 10, EMapObject::VillageBlock1);
	AddMapObject(10, 11, EMapObject::VillageBlock2);
	AddMapObject(10, 12, EMapObject::VillageBlock1);
	AddMapObject(10, 13, EMapObject::VillageBlock2);

	AddMapObject(11, 2, EMapObject::VillageBlock1);
	AddMapObject(11, 3, EMapObject::VillageBlock2);
	AddMapObject(11, 4, EMapObject::VillageBlock1);
	AddMapObject(11, 5, EMapObject::VillageTree);
	AddMapObject(11, 6, EMapObject::VillageMoveBlock);
	AddMapObject(11, 7, EMapObject::VillageMoveBlock);
	AddMapObject(11, 9, EMapObject::VillageTree);
	AddMapObject(11, 10, EMapObject::VillageMoveBlock);
	AddMapObject(11, 11, EMapObject::VillageRedHouse);
	AddMapObject(11, 12, EMapObject::VillageMoveBlock);
	AddMapObject(11, 13, EMapObject::VillageRedHouse);

	AddMapObject(12, 0, EMapObject::VillageBlueHouse);
	AddMapObject(12, 2, EMapObject::VillageBlueHouse);
	AddMapObject(12, 3, EMapObject::VillageBlock1);
	AddMapObject(12, 4, EMapObject::VillageBlueHouse);
	AddMapObject(12, 5, EMapObject::TownBush);
	AddMapObject(12, 8, EMapObject::VillageMoveBlock);
	AddMapObject(12, 9, EMapObject::TownBush);
	AddMapObject(12, 10, EMapObject::VillageBlock2);
	AddMapObject(12, 11, EMapObject::VillageBlock1);
	AddMapObject(12, 12, EMapObject::VillageBlock2);
}
