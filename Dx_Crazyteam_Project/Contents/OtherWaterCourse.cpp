#include "PreCompile.h"
#include "OtherWaterCourse.h"
#include <EngineCore/Collision.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Game_Core.h"
#include "Packets.h"
#include "EngineBase/EngineTime.h"

AOtherWaterCourse::AOtherWaterCourse()
{
	UEngineTime Time;
	OherBomb_MilliSecond = Time.GetCurTime().MilliSecond;
	OherBomb_Second = Time.GetCurTime().Second;
}

AOtherWaterCourse::~AOtherWaterCourse()
{
}

void AOtherWaterCourse::BeginPlay()
{
	AWaterCourse::BeginPlay();

	Sub_MilliSecond = OherBomb_MilliSecond - Bomb_MilliSecond;
	Sub_Second = OherBomb_Second - Bomb_Second;
	OtherCreate = true;
}

void AOtherWaterCourse::Tick(float _DeltaTime)
{
	std::shared_ptr<UEngineProtocol> Protocol = nullptr;

	do
	{
		Protocol = PopProtocol();
		if (nullptr == Protocol)
		{
			break;
		}
		EContentPacket PacketType = Protocol->GetPacketType<EContentPacket>();

		switch (PacketType)
		{
		case WaterCourseUpdatePacket:
		{

			std::shared_ptr<UWaterWaterCourseUpdatePacket> UpdatePacket = std::dynamic_pointer_cast<UWaterWaterCourseUpdatePacket>(Protocol);

			if (UpdatePacket->ObjectType == static_cast<int>(EObjectType::WaterCourse))
			{
				SetActorLocation(UpdatePacket->Pos);
			}
			break;
		}
		default:
			break;
		}
	} while (nullptr != Protocol);


	AWaterCourse::Tick(_DeltaTime);
}

