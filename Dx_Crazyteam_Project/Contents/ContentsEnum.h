#pragma once

enum class EObjectOrder
{
	None,
	Background,
	Map,
	BlockFront,
	Player,
	BlockBack,
	WaterBomb,
	UI,
};

enum class ECollisionOrder
{
	Player,
	Monster,
};

enum class ERenderOrder
{
	Back,
	Player,
	Test,
};

enum class EMapObjectType {
	None,
	Block,   //움직이지도 부서지지도 않는 블록
	BrakableBlock,   //부서지는 블록
	MoveBlock,     //움직이는 블록
	Bush,          //부시
	WaterBalloon,  //물풍선
};

enum class EMapObject
{
	NormalBlock,
	CampBlock,
};