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
	Lobby_Player_Select= 97,
	UIPacket = 98,
	ActorUpdatePacket = 99,
	MapObjectUpdatePacket = 100,
};

// 설명 :
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
		_Ser << SpriteAlpha;
		_Ser << RendererIsActive;
		_Ser << RendererPos;
		_Ser << TeamType;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
		_Ser >> AnimationInfo;
		_Ser >> ObjectType;
		_Ser >> SpriteName;
		_Ser >> IsDestroy;
		_Ser >> SpriteAlpha;
		_Ser >> RendererIsActive;
		_Ser >> RendererPos;
		_Ser >> TeamType;
	}

public:
	float4 Pos = float4::Zero;
	int AnimationInfo = 0;
	int ObjectType = 0;
	bool IsDestroy = true;
	std::string SpriteName;
	float SpriteAlpha = 1.0f;
	bool RendererIsActive = true;
	float4 RendererPos = float4::Zero;
	int TeamType = 0;
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
		_Ser << Time_Second;
		_Ser << Seconds_Units;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> ClientCreate;
		_Ser >> Time_Second;
		_Ser >> Seconds_Units;
	}

public:
	bool ClientCreate = false;
	bool SerVerSend = false;
	int Time_Second = 0;
	int Seconds_Units = 0;

};



// 설명 :
class UMapObjectUpdatePacket : public UEngineProtocol
{
public:
	static const EContentPacket Type = EContentPacket::MapObjectUpdatePacket;
public:
	UMapObjectUpdatePacket()
	{
		SetType(EContentPacket::MapObjectUpdatePacket);
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




class ULobbyPlayerUpdatePacket : public UEngineProtocol
{
public:
	static const EContentPacket Type = EContentPacket::Lobby_Player_Select;
public:
	ULobbyPlayerUpdatePacket()
	{
		SetType(EContentPacket::Lobby_Player_Select);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << NewPlayer;
		_Ser << SpriteNames;
		_Ser << MapName;
		_Ser << ChangeMaP;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> NewPlayer;
		_Ser >> SpriteNames;
		_Ser >> MapName;
		_Ser >> ChangeMaP;
	}

public:
	bool NewPlayer = false;
	std::vector<std::string> SpriteNames;
	std::string MapName = "";
	bool ChangeMaP = false;
};

