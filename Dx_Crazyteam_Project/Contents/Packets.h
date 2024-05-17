#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineProtocol.h>

enum class EObjectType
{
	Player = 2000,
	Item,
	WaterBomb,
	WaterCourse,
};

enum EContentPacket
{
	UIPacket = 96,
	WaterCourseUpdatePacket = 97,
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
		_Ser << ObjectType;
		_Ser << SpriteName;
		_Ser << IsDestroy;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
		_Ser >> AnimationInfo;
		_Ser >> ObjectType;
		_Ser >> SpriteName;
		_Ser >> IsDestroy;
	}

public:
	float4 Pos = float4::Zero;
	int AnimationInfo = 0;
	int ObjectType = 0;
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
		_Ser << ObjectType;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
		_Ser >> ObjectType;
	}

public:
	float4 Pos = float4::Zero;
	int ObjectType = 0;
};


class UWaterWaterCourseUpdatePacket : public UEngineProtocol
{
public:
	static const EContentPacket Type = EContentPacket::WaterCourseUpdatePacket;
public:
	UWaterWaterCourseUpdatePacket()
	{
		SetType(EContentPacket::WaterCourseUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << Pos;
		_Ser << ObjectType;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
		_Ser >> ObjectType;
	}

public:
	float4 Pos = float4::Zero;
	int ObjectType = 0;
};



class UUIUpdatePacket : public UEngineProtocol
{
public:
	static const EContentPacket Type = EContentPacket::UIPacket;
public:
	UUIUpdatePacket()
	{
		SetType(EContentPacket::UIPacket);
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
	int ObjectType = 0;
};
