#pragma once


class ConstValue
{
public:
	static const FVector TileSize;
	static const int TileY;
	static const int TileX;

	static const int dy[];
	static const int dx[];

	static const int BazziDefaultSpeed = 5;
	static const int BazziDefaultWBCount = 1;
	static const int BazziDefaultWBPower = 1;
	static const int BazziMaxSpeed = 9;
	static const int BazziMaxWBCount = 6;
	static const int BazziMaxWBPower = 7;

	static const int DaoDefaultSpeed = 5;
	static const int DaoDefaultWBCount = 1;
	static const int DaoDefaultWBPower = 1;
	static const int DaoMaxSpeed = 7;
	static const int DaoMaxWBCount = 10;
	static const int DaoMaxWBPower = 7;

	static const int MaridDefaultSpeed = 4;
	static const int MaridDefaultWBCount = 2;
	static const int MaridDefaultWBPower = 1;
	static const int MaridMaxSpeed = 8;
	static const int MaridMaxWBCount = 9;
	static const int MaridMaxWBPower = 6;

	static EMap SelectedMap;
	static ETeamType MainPlayerTeamType;
	static ECharacterType MainPlayerCharacterType;
};