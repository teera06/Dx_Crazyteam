#include "PreCompile.h"

#include "ServerTestOtherPlayer.h"

AServerTestOtherPlayer::AServerTestOtherPlayer()
	:APlayer()
{
}

AServerTestOtherPlayer::~AServerTestOtherPlayer()
{
}

void AServerTestOtherPlayer::BeginPlay()
{
	Super::BeginPlay();

	OffIsSendPacket();
}

void AServerTestOtherPlayer::Tick(float _DeltaTime)
{
	InputOff();

	Super::Tick(_DeltaTime);
}