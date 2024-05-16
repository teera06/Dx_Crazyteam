#include "PreCompile.h"
#include "Item.h"
#include "BaseMap.h"
#include "CAGameMode.h"
AItem::AItem()
{
	FrontRenderer = CreateDefaultSubObject<USpriteRenderer>("ItemRender");
	FrontRenderer->SetupAttachment(Root);

	BackRenderer = CreateDefaultSubObject<USpriteRenderer>("ItemShadowRender");
	BackRenderer->SetupAttachment(Root);
}

AItem::~AItem()
{
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	FrontRenderer->SetOrder(ERenderOrder::Item);

	BackRenderer->CreateAnimation("ItemShadow", "ItemShadow.png", 0.9f, true, 0, 1);
	BackRenderer->ChangeAnimation("ItemShadow");
	BackRenderer->SetAutoSize(0.6f, true);
	BackRenderer->AddPosition(FVector::Down * 65.f);
	BackRenderer->SetOrder(ERenderOrder::Shadow);
	//BackRenderer->SetMulColor(FVector(1.f, 1.f, 1.f, 0.6f));


	SetType(EMapObjectType::Item);

	WaterInteract = [&]
		{
			if (bWaterInteract) return;


			GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
		};

	PlayerInteract = [&] {
		if(bPlayerInteract) return;

		Action();
		};
}

void AItem::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}