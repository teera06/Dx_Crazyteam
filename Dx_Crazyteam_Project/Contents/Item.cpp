#include "PreCompile.h"
#include "Item.h"
#include "BaseMap.h"
#include "CAGameMode.h"
#include "SendPacketManager.h"
#include "Bush.h"

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
			if (GetIsPossessed())
			{
				std::shared_ptr<AMapObject> MapObj = GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y, GetCurPos().x);
				if (MapObj != nullptr)
				{
					ABush* Bush = dynamic_cast<ABush*>(GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y, GetCurPos().x).get());

					Bush->SetPossessBlock(nullptr);
				}
				Destroy();
			}
			else
			{
				GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
			}
		};

	PlayerInteract = [&] {

		{
			USendPacketManager::SendMapObjectReleasePacket(this, GetCurPos());
		}

		Action();
		};
}

void AItem::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}