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

	FrontRenderer->CreateAnimation("ItemBubble", "Bubble(1).png", 0.3f, true, 0, 5);
	FrontRenderer->ChangeAnimation("ItemBubble");
	FrontRenderer->SetAutoSize(1.f, true);
}

void AItemBubble::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}