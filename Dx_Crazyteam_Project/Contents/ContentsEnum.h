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