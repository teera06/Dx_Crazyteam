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
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
		_Ser >> IsDestroy;
	}

public:
	POINT Pos = { 0,0 };
	bool IsDestroy = true;

protected:

private:

};

