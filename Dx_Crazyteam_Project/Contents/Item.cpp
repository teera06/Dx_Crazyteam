#include "PreCompile.h"
#include "Item.h"

AItem::AItem()
{
	FrontRenderer = CreateDefaultSubObject<USpriteRenderer>("ItemRender");
	FrontRenderer->SetupAttachment(Root);
	FrontRenderer->SetOrder(ERenderOrder::Item);
}

AItem::~AItem()
{
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

void AItem::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}