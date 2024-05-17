#include "PreCompile.h"

#include "ServerTestOtherPlayer.h"

AServerTestOtherPlayer::AServerTestOtherPlayer()
	:AServerTestPlayer()
{
	OffIsSendPacket();
}

AServerTestOtherPlayer::~AServerTestOtherPlayer()
{
}

void AServerTestOtherPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AServerTestOtherPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}