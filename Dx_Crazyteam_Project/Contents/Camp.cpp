#include "PreCompile.h"
#include "Camp.h"
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
	Renderer->SetOrder(ERenderOrder::Map);

	AddObjectInit();
}

void ACamp::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ACamp::AddObjectInit()
{
	for (int y = 1; y < ConstValue::TileY - 1; y += 2)
	{
		for (int x = 1; x < ConstValue::TileX; x += 2)
		{
			AddMapObject(y, x, EMapObject::CampBlock);
		}
	}
	AddMapObject(0, 1, EMapObject::CampBlock);
}

