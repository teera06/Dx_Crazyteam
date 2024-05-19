#include "PreCompile.h"
#include "Item.h"
#include "BaseMap.h"
#include "CAGameMode.h"
#include "SendPacketManager.h"

AItem::AItem()
{

}

AItem::~AItem()
{
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("ItemShadow", "ItemShadow.png", 0.9f, true, 0, 1);
	Renderer->ChangeAnimation("ItemShadow");
	Renderer->SetAutoSize(0.6f, true);
	//Renderer->AddPosition(FVector::Down * 65.f);

	SetType(EMapObjectType::Item);

	WaterInteract = [&]
		{
			GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
		};

	PlayerInteract = [&] {

		{
			USendPacketManager::SendItemReleasePacket(this, GetCurPos());
		}

		Action();
		};
}

void AItem::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}