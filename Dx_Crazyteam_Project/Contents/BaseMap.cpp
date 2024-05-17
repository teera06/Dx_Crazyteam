#include "PreCompile.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <algorithm>

#include "BaseMap.h"
#include "Block.h"
#include "CampBlock1.h"
#include "WaterBomb.h"
#include "WaterCourse.h"
#include "Bush.h"
#include "DummyBlock.h"
#include "CampMoveBlock1.h"
#include "CampHpBlock.h"
#include "CAGameMode.h"
#include "Player.h"
#include "ItemBubble.h"
#include "ItemNiddle.h"
#include "ItemOwl.h"
#include "ItemRoller.h"
#include "ItemFluid.h"
#include "ItemShoes.h"
#include "Packets.h"
#include "Game_Core.h"
#include "TownBush.h"
#include "MapStateValue.h"

ABaseMap::ABaseMap()
{

}

ABaseMap::~ABaseMap()
{
}

bool ABaseMap::IsMove(FVector _CheckPos)
{
	if (_CheckPos.X > ConstValue::TileSize.X / 2.f * ConstValue::TileX ||
		_CheckPos.X < ConstValue::TileSize.X / 2.f * (-ConstValue::TileX))
	{
		return false;
	}

	if (_CheckPos.Y > ConstValue::TileSize.Y / 2.f * (ConstValue::TileY-1) ||
		_CheckPos.Y < ConstValue::TileSize.Y / 2.f * (-(ConstValue::TileY-1)))
	{
		return false;
	}

	POINT CheckPoint = PosToPoint(_CheckPos);

	if (MapStatus[CheckPoint.y][CheckPoint.x] == nullptr) return true;

	switch (MapStatus[CheckPoint.y][CheckPoint.x]->GetType())
	{
		case EMapObjectType::None:
		case EMapObjectType::Water:
		{
			return true;
		}
		break;

		case EMapObjectType::WaterBalloon:
		{
			std::shared_ptr<APlayer> Player = GetGameMode()->GetPlayer();
			POINT PlayerPoint = Player->GetPlayerInfo()->CurIndex;
			POINT CheckPoint = PosToPoint(_CheckPos);
			if (CheckPoint.x != PlayerPoint.x ||
				CheckPoint.y != PlayerPoint.y)
			{
				return false;
			}
			else return true;
		}
		case EMapObjectType::Block:
		{
			FVector TilePosition = MapStatus[CheckPoint.y][CheckPoint.x]->GetActorLocation();

			if (TilePosition.X + ConstValue::TileSize.X / 2.f > _CheckPos.X &&
				TilePosition.X - ConstValue::TileSize.X / 2.f < _CheckPos.X &&
				TilePosition.Y + ConstValue::TileSize.Y / 2.f > _CheckPos.Y &&
				TilePosition.Y - ConstValue::TileSize.Y / 2.f < _CheckPos.Y)
			{
				POINT CheckPoint = PosToPoint(_CheckPos);

				if (MapStatus[CheckPoint.y][CheckPoint.x] == nullptr) return true;

				MapStatus[CheckPoint.y][CheckPoint.x]->PlayerInteract();
				return false;
			}

			return true;
		}
		break;
		case EMapObjectType::Item:
		{
			POINT CheckPoint = PosToPoint(_CheckPos);
			MapStatus[CheckPoint.y][CheckPoint.x]->PlayerInteract();
			return true;
		}
		break;
		case EMapObjectType::Bush:
		{
			POINT CheckPoint = PosToPoint(_CheckPos);
			MapStatus[CheckPoint.y][CheckPoint.x]->PlayerInteract();
			return true;
		}
		break;
		default:
			return true;
			break;
	}
}

bool ABaseMap::IsEmpty(FVector _PlayerPos)
{
	POINT PlayerPoint = PosToPoint(_PlayerPos);

	if (MapStatus[PlayerPoint.y][PlayerPoint.x] = nullptr)
	{
		return true;
	}

	return false;
}

bool ABaseMap::IsEmpty(int _Y, int _X)
{

	if (MapStatus[_Y][_X] == nullptr)
	{
		return true;
	}

	return false;
}

bool ABaseMap::IsOnWater(FVector _PlayerPos)
{
	POINT CheckPos = PosToPoint(_PlayerPos);
	
	if (MapStatus[CheckPos.y][CheckPos.x] == nullptr) return false;

	EMapObjectType Type = MapStatus[CheckPos.y][CheckPos.x]->GetType();
	
	if (Type == EMapObjectType::Water) return true;
	else return false;
}

bool ABaseMap::IsOnBush(FVector _PlayerPos)
{
	POINT CheckPos = PosToPoint(_PlayerPos);

	if (MapStatus[CheckPos.y][CheckPos.x] == nullptr) return false;

	EMapObjectType Type = MapStatus[CheckPos.y][CheckPos.x]->GetType();

	if (Type == EMapObjectType::Bush) return true;
	else return false;
}

bool ABaseMap::IsOnBush(int _Y, int _X)
{
	if (MapStatus[_Y][_X] == nullptr) return false;

	EMapObjectType Type = MapStatus[_Y][_X]->GetType();

	if (Type == EMapObjectType::Bush) return true;
	else return false;
}



void ABaseMap::BeginPlay()
{
	Super::BeginPlay();

	AddActorLocation(FVector(0.f, ConstValue::TileSize.Y / 2.f, 0.f));
	
	for (int y = 0; y < ConstValue::TileY-1; y++)
	{
		std::vector<std::shared_ptr<AMapObject>> Temp;
		MapStatus.push_back(Temp);
		for (int x = 0; x < ConstValue::TileX; x++)
		{
			MapStatus[y].push_back(nullptr);
		}
	}

	FVector Pos = GetActorLocation();
	Pos.Z = 300.f;
	SetActorLocation(Pos);
}

void ABaseMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}


std::shared_ptr<AMapObject> ABaseMap::AddMapObject(int _Y, int _X, EMapObject _MapObjectType, EItemType _Item)
{
	FVector PushPos = PointToPos(_Y, _X);


	std::shared_ptr<AMapObject> MapObj = nullptr;
	switch (_MapObjectType)
	{
	case EMapObject::Default:
	{
		MapObj = GetWorld()->SpawnActor<AMapObject>("Default");
		break;
	}
	case EMapObject::DummyBlock:
	{
		MapObj = GetWorld()->SpawnActor<ADummyBlock>("Block");
		break;
	}
	case EMapObject::CampMoveBlock1:
	{
		MapObj = GetWorld()->SpawnActor<ACampMoveBlock1>("CampMoveBlock1");
		break;
	}
	case EMapObject::CampMoveBlock2:
	{

	}
	case EMapObject::NormalBlock:
	{
		MapObj = GetWorld()->SpawnActor<ABlock>("Block");
		break;
	}
	case EMapObject::CampBlock1:
	{
		MapObj = GetWorld()->SpawnActor<ACampBlock1>("CampBlock1");
		break;
	}
	case EMapObject::CampBlock2:
	{
		
	}
	case EMapObject::CampBlock3:
	{
		
	}
	case EMapObject::CampBlock4:
	{
		
	}
	case EMapObject::TownBush:
	{
		MapObj = GetWorld()->SpawnActor<ATownBush>("TownBush");
		break;
	}
	case EMapObject::CampHPBlock:
	{
		MapObj = GetWorld()->SpawnActor<ACampHpBlock>("CampHPBlock");
		break;
	}
	case EMapObject::WaterBomb:
	{
		std::shared_ptr<AWaterBomb> TempObj = GetWorld()->SpawnActor<AWaterBomb>("CampBlock");
		TempObj->SetActorLocation(PushPos);
		TempObj->CreateWaterBomb();
		UMapStateValue::st_ACAGameMode = GetGameMode();
		MapObj = TempObj;
		break;
	}
	case EMapObject::Water:
	{
		std::shared_ptr<AWaterCourse> TempObj = GetWorld()->SpawnActor<AWaterCourse>("CampBlock");
		TempObj->SetActorLocation(PushPos);
		TempObj->CreateWaterCenter();
		MapObj = TempObj;
		break;
	}
	case EMapObject::Item:
	{
		MapObj = SpawnItemObject(_Y, _X, _Item);
		break;
	}
	default:
		break;
	}

	if (MapObj == nullptr) 
	{
		return nullptr;
	}

	MapObj->SetActorLocation(PushPos);
	MapObj->SetCurPos(POINT(_X, _Y));
	MapObj->SetCurGameMode(GetGameMode());

	if (MapStatus[_Y][_X] != nullptr)
	{
		MapStatus[_Y][_X]->Destroy();
	}

	MapStatus[_Y][_X] = MapObj;

	return MapObj;
}

std::shared_ptr<AMapObject> ABaseMap::AddWaterCourse(int _Y, int _X, bool _IsEnd, EEngineDir _Dir)
{
	std::shared_ptr<AMapObject> MapObj = nullptr;

	FVector PushPos = PointToPos(_Y, _X);

	std::shared_ptr<AWaterCourse> TempObj = GetWorld()->SpawnActor<AWaterCourse>("CampBlock");
	TempObj->SetActorLocation(PushPos);
	TempObj->SetDir(_Dir);
	if (false == _IsEnd)
	{
		TempObj->CreateWaterStream();
	}
	else
	{
		TempObj->CreateWaterEndStem();
	}
	MapObj = TempObj;


	MapObj->SetActorLocation(PushPos);
	MapObj->SetCurPos(POINT(_X, _Y));
	MapObj->SetCurGameMode(GetGameMode());

	if (MapStatus[_Y][_X] != nullptr)
	{
		MapStatus[_Y][_X]->Destroy();
	}

	MapStatus[_Y][_X] = MapObj;

	return MapObj;
}

void ABaseMap::PushMapObject(std::shared_ptr<AMapObject> _Obj, int _Y, int _X)
{
	if (MapStatus[_Y][_X] != nullptr)
	{
		MapStatus[_Y][_X]->Destroy();
	}

	FVector PushPos = PointToPos(_Y, _X);

	_Obj->SetActorLocation(PushPos);
	_Obj->SetCurPos(POINT(_X, _Y));
	_Obj->SetCurGameMode(GetGameMode());

	MapStatus[_Y][_X] = _Obj;
}

void ABaseMap::MoveMapObject(std::shared_ptr<AMapObject> _Obj, int _NY, int _NX, int _PY, int _PX)
{
	if (MapStatus[_NY][_NX] == nullptr)
	{
		PushMapObject(_Obj, _NY, _NX);
		_Obj->SetIsPossessed(false);
		if (!(MapStatus[_PY][_PX]->GetType() == EMapObjectType::Bush))
		{
			MapStatus[_PY][_PX] = nullptr;
		}
	}
	else
	{
		if (MapStatus[_NY][_NX]->GetType() == EMapObjectType::Bush)
		{
			ABush* Bush = dynamic_cast<ABush*>(MapStatus[_NY][_NX].get());
			Bush->SetPossessBlock(_Obj);

			FVector PushPos = PointToPos(_NY, _NX);

			_Obj->SetActorLocation(PushPos);
			_Obj->SetCurPos(POINT(_NX, _NY));
			_Obj->SetCurGameMode(GetGameMode());
			_Obj->SetIsPossessed(true);

			if (!(MapStatus[_PY][_PX]->GetType() == EMapObjectType::Bush))
			{
				MapStatus[_PY][_PX] = nullptr;
			}


		}
	}
}

std::shared_ptr<AMapObject> ABaseMap::SpawnItemObject(int _Y, int _X, EItemType _Item)
{
	if (_Item == EItemType::None) return nullptr;

	std::shared_ptr<AMapObject> Item = nullptr;

	switch (_Item)
	{
	case EItemType::None:
		return nullptr;
		break;
	case EItemType::ItemBubble:
		Item = GetWorld()->SpawnActor<AItemBubble>("Bubble");
		break;
	case EItemType::ItemFluid:
		Item = GetWorld()->SpawnActor<AItemFluid>("Fluid");
		break;
	case EItemType::ItemRoller:
		Item = GetWorld()->SpawnActor<AItemRoller>("Roller");
		break;
	case EItemType::ItemOwl:
		Item = GetWorld()->SpawnActor<AItemOwl>("Owl");
		break;
	case EItemType::ItemShoes:
		Item = GetWorld()->SpawnActor<AItemShoes>("Shoes");
		break;
	case EItemType::ItemNiddle:
		Item = GetWorld()->SpawnActor<AItemNiddle>("Niddle");
		break;
	default:
		break;
	}

	return Item;
}

std::shared_ptr<AMapObject> ABaseMap::SpawnWaterBomb(FVector _SpawnPos)
{
	POINT BombPoint = PosToPoint(_SpawnPos);

	return AddMapObject(BombPoint.y, BombPoint.x, EMapObject::WaterBomb);
}

std::shared_ptr<AMapObject> ABaseMap::SpawnWaterBomb(int _Y, int _X)
{
	return AddMapObject(_Y, _X, EMapObject::WaterBomb);
}

void ABaseMap::DestroyMapObject(int _Y, int _X)
{
	//EMapObjectType Type = MapStatus[_Y][_X]->GetType();

	//switch (Type)
	//{
	////case EMapObjectType::Block:
	////	break;
	////case EMapObjectType::Bush:
	////	break;
	////case EMapObjectType::Water:
	////	break;
	////case EMapObjectType::WaterBalloon:
	////	break;
	//case EMapObjectType::Item:
	//{
	//	int ReleaseObjectToken = MapStatus[_Y][_X]->GetObjectToken();

	//	std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();
	//	Packet->SetObjectToken(ReleaseObjectToken);
	//	Packet->IsDestroy = true;
	//	Packet->ObjectType = static_cast<int>(EObjectType::Item);
	//	UGame_Core::Net->Send(Packet);
	//	break;
	//}
	//default:
	//	break;
	//}
	
	MapStatus[_Y][_X]->Destroy();
	MapStatus[_Y][_X] = nullptr;
}

POINT ABaseMap::PosToPoint(FVector _PlayerPos)
{
	float MinDistance = 999999;
	POINT Result = { 0,0 };

	FVector PlayerPos = _PlayerPos;
	PlayerPos.Z = 0.f;


	for (int y = 0; y < ConstValue::TileY - 1; y++)
	{
		for (int x = 0; x < ConstValue::TileX; x++)
		{
			FVector TileLocation = PointToPos(y,x);
			TileLocation.Z = 0.f;

			float Distance = (PlayerPos - TileLocation).Size3D();

			if (Distance < MinDistance)
			{
				MinDistance = min(Distance, MinDistance);
				Result = { x,y };
			}
		}
	}

	return Result;
}

FVector ABaseMap::PointToPos(int _Y, int _X)
{
	FVector FirstPos = FVector::Zero;

	FirstPos.X = -ConstValue::TileSize.X * static_cast<float>((ConstValue::TileX / 2));
	FirstPos.Y = ConstValue::TileSize.Y * static_cast<float>((ConstValue::TileY - 1) / 2);

	FVector PushPos = FVector::Zero;

	PushPos.X = FirstPos.X + ConstValue::TileSize.X * _X;
	PushPos.Y = FirstPos.Y - ConstValue::TileSize.Y * _Y;

	return PushPos;
}
