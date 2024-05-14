#include "PreCompile.h"
#include "Camp.h"
#include <EngineCore/DefaultSceneComponent.h>

ACamp::ACamp() 
{
	BackMap = CreateDefaultSubObject<USpriteRenderer>("BackMap");
	BackMap->SetupAttachment(Root);
}

ACamp::~ACamp() 
{
}

void ACamp::BeginPlay()
{
	Super::BeginPlay();

	BackMap->SetSprite("Camp_Back1.png");
	BackMap->SetAutoSize(1.f, true);
	BackMap->SetOrder(EObjectOrder::Map);

	//AddObjectInit();
}

void ACamp::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ACamp::AddObjectInit()
{
	for (int y = 1; y < TileY - 1; y += 2)
	{
		for (int x = 1; x < TileX; x += 2)
		{
			AddMapObject(y, x, EMapObject::CampBlock);
		}
	}
	
}

