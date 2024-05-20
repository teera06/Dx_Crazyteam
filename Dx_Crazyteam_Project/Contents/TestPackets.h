#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineProtocol.h>


enum ETestContentPacket
{
	MapObjectUpdatePacket = 100,
};

// Ό³Έν :
class UMapObjectUpdatePacket : public UEngineProtocol
{
public:
	static const ETestContentPacket Type = ETestContentPacket::MapObjectUpdatePacket;
public:
	UMapObjectUpdatePacket()
	{
		SetType(ETestContentPacket::MapObjectUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << Pos;
		_Ser << IsDestroy;
		_Ser << ItemType;
		_Ser << ObjectType;
		_Ser << IsMove;
		_Ser << MovePos;
		_Ser << IsMoveEnd;
		_Ser << MoveBeginPos;
		_Ser << MoveEndPos;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
		_Ser >> IsDestroy;
		_Ser >> ItemType;
		_Ser >> ObjectType;
		_Ser >> IsMove;
		_Ser >> MovePos;
		_Ser >> IsMoveEnd;
		_Ser >> MoveBeginPos;
		_Ser >> MoveEndPos;
	}

public:
	POINT Pos = { 0,0 };
	bool IsDestroy = false;
	int ItemType = static_cast<int>(EItemType::None);
	int ObjectType = static_cast<int>(EMapObject::Default);
	bool IsMove = false;
	FVector MovePos = FVector::Zero;
	bool IsMoveEnd = false;
	POINT MoveBeginPos = { 0,0 };
	POINT MoveEndPos = { 0,0 };

protected:

private:

};

