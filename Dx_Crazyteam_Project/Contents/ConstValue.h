#pragma once
class ConstValue
{
public:
	static const FVector TileSize;
	static const int TileY;
	static const int TileX;

	static const int dy[];
	static const int dx[];

	static const int BazziMaxSpeed = 9;
	static const int BazziMaxWBCount = 6;
	static const int BazziMaxWBPower = 7;

	static const int DaoMaxSpeed = 7;
	static const int DaoMaxWBCount = 10;
	static const int DaoMaxWBPower = 7;
};