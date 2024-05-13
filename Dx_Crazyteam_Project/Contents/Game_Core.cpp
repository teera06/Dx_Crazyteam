#include "PreCompile.h"
#include "Game_Core.h"
#include "ServerGameMode.h"
#include "testGameMode.h"

std::shared_ptr<UEngineNet> UGame_Core::Net = nullptr;

UGame_Core::UGame_Core()
{
}

UGame_Core::~UGame_Core()
{
}

void UGame_Core::Initialize()
{
	GEngine->CreateLevel<AtestGameMode>("testGameMode");
	GEngine->ChangeLevel("testGameMode");

}
