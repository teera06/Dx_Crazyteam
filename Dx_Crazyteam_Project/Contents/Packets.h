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

// ���� :
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
		_Ser << Bomb;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
		_Ser >> ObjectType;
		_Ser >> Bomb;
	}

public:
	float4 Pos = float4::Zero;
	int ObjectType = 0;
	bool Bomb = false;
};


class UWaterCourseUpdatePacket : public UEngineProtocol
{
public:
	static const EContentPacket Type = EContentPacket::WaterCourseUpdatePacket;
public:
	UWaterCourseUpdatePacket()
	{
		SetType(EContentPacket::WaterCourseUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << Pos;
		_Ser << ObjectType;
		_Ser << Dir;
		_Ser >> SetCourse;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
		_Ser >> ObjectType;
		_Ser >> Dir;
		_Ser >> SetCourse;
	}

public:
	float4 Pos = float4::Zero;
	int ObjectType = 0;
	int Dir = 0;
	bool SetCourse = false;
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
		_Ser << ClientCreate;
		_Ser << Second_Tens;
		_Ser << Seconds_Units;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> ClientCreate;
		_Ser >> Second_Tens;
		_Ser >> Seconds_Units;
	}

public:
	bool ClientCreate = false;
	bool SerVerSend = false;
	int Second_Tens = 0;
	int Seconds_Units = 0;

};
