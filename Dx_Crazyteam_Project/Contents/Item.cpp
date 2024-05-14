#include "PreCompile.h"
#include "Item.h"

AItem::AItem()
{
	//Root = CreateDefaultSubObject<UDefaultSceneComponent>("RendererRoot");
	SetRoot(Root);

	FrontRenderer = CreateDefaultSubObject<USpriteRenderer>("ItemRender");
	FrontRenderer->SetupAttachment(Root);
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