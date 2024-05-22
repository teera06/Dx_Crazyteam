#pragma once
#include "PreCompile.h"
#include "ConstValue.h"

const FVector ConstValue::TileSize = FVector(40.f, 40.f, 10.f);
const int ConstValue::TileY = 14;
const int ConstValue::TileX = 15;

const int ConstValue::dy[] = { -1,0,1,0 };
const int ConstValue::dx[] = { 0,1,0,-1 };

ETeamType ConstValue::MainPlayerTeamType = ETeamType::None;
ECharacterType ConstValue::MainPlayerCharacterType = ECharacterType::None;

EMap ConstValue::SelectedMap = EMap::Village;