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
bool ConstValue::MainPlayerIsDie = false;

EMap ConstValue::SelectedMap = EMap::Village;

const FVector ConstValue::CameraPos = FVector(80.f, 1.0f, -1000.f);

const std::vector<POINT> ConstValue::VillageStartPos = { {0,0},{7,0},{13,1},{1,11},{6,12},{14,12},{0,0},{0,0},{0,0},{0,0},{0,0} };
//const std::vector<POINT> ConstValue::CampStartPOINT;
