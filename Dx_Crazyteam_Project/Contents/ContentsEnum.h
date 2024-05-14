#pragma once

enum class ERenderOrder
{
	None,
	Background,
	Map,
	Shadow,
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

enum class EMapObjectType {
	None,
	Block,   //움직이지도 부서지지도 않는 블록 / 물풍선
	BrakableBlock,   //부서지는 블록
	MoveBlock,     //움직이는 블록
	Bush,          //부시
	Water,  //물풍선
	WaterBalloon,

};

enum class EMapObject
{
	NormalBlock,
	CampBlock,
	WaterBomb,
};

enum class ECharacterType
{
	None,
	Bazzi,
	Dao,
	Marid,
};

enum class ECADir
{
	None,
	Right,
	Left,
	Up,
	Down,
};