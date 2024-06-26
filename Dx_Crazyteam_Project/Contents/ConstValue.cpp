#pragma once
#include "PreCompile.h"
#include "ConstValue.h"

const FVector ConstValue::TileSize = FVector(40.f, 40.f, 10.f);
const int ConstValue::TileY = 14;
const int ConstValue::TileX = 15;

const int ConstValue::dy[] = { -1,0,1,0 };
const int ConstValue::dx[] = { 0,1,0,-1 };

ETeamType ConstValue::MainPlayerTeamType = ETeamType::ATeam;
ECharacterType ConstValue::MainPlayerCharacterType = ECharacterType::Bazzi;
bool ConstValue::MainPlayerIsDie = false;

EMapType ConstValue::SelectedMap = EMapType::Village;

const FVector ConstValue::CameraPos = FVector(80.f, 1.0f, -1000.f);

const std::vector<POINT> ConstValue::VillageStartPOINT = { {0,0},{7,0},{13,1},{1,11},{6,12},{14,12},{6,7},{6,7},{6,7},{6,7},{6,7} };
const std::vector<POINT> ConstValue::CampStartPOINT = { {2,1},{3,3},{3,7},{2,11},{12,1},{11,3},{11,7},{12,11},{6,7},{6,7},{6,7} };
