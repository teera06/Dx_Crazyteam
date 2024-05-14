#include "PreCompile.h"
#include "ItemBubble.h"

AItemBubble::AItemBubble()
{
	SetItemType(EItemType::ItemBubble);
}

AItemBubble::~AItemBubble()
{
}

void AItemBubble::BeginPlay()
{
	Super::BeginPlay();

	FrontRenderer->CreateAnimation("ItemBubble", "Bubble(1).png", true, 0, 5);
	FrontRenderer->ChangeAnimation("ItemBubble");
}

void AItemBubble::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}