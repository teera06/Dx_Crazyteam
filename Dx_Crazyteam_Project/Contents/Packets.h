#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineProtocol.h>

enum EContentPacket
{
	WaterBombUpdatePacket = 98,
	ActorUpdatePacket = 99,
};

// Ό³Έν :
class UActorUpdatePacket : public UEngineProtocol
{
public: 
	static const EContentPacket Type = EContentPacket::ActorUpdatePacket;
public: 
	UActorUpdatePacket()
	{ 
		SetType(EContentPacket::ActorUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << Pos;
		_Ser << AnimationInfo;
		_Ser << SpriteName;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
		_Ser >> AnimationInfo;
		_Ser >> SpriteName;
	}

public:
	float4 Pos = float4::Zero;
	int AnimationInfo = 0;
	// int ObjectType = 0;
	bool IsDestroy = true;
	std::string SpriteName;
};


class UWaterBombUpdatePacket : public UEngineProtocol
{
public:
	static const EContentPacket Type = EContentPacket::WaterBombUpdatePacket;
public:
	UWaterBombUpdatePacket()
	{
		SetType(EContentPacket::WaterBombUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << Pos;
		_Ser << AnimationInfo;
		_Ser << SpriteName;
		_Ser << IsDestroy;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
		_Ser >> AnimationInfo;
		_Ser >> SpriteName;
		_Ser >> IsDestroy;
	}

public:
	float4 Pos = float4::Zero;
	int AnimationInfo = 0;
	// int ObjectType = 0;
	bool IsDestroy = true;
	std::string SpriteName;
};
