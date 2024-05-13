#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineProtocol.h>

enum ContentPacket
{
	ActorUpdatePacket = 99,
};

// Ό³Έν :
class UActorUpdatePacket : public UEngineProtocol
{
public: 
	static const ContentPacket Type = ContentPacket::ActorUpdatePacket;
public: 
	UActorUpdatePacket()
	{ 
		SetType(ContentPacket::ActorUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << Pos;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
	}

public:
	float4 Pos = float4::Zero;
	// int ObjectType = 0;
	bool IsDestroy = true;
	std::string SpriteName;
};

