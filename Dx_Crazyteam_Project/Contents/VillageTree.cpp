#include "PreCompile.h"
#include "VillageTree.h"

AVillageTree::AVillageTree() 
{
}

AVillageTree::~AVillageTree() 
{
}

void AVillageTree::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("TownTree.png");
}

void AVillageTree::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

