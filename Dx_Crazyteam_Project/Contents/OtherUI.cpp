#include "PreCompile.h"
#include "OtherUI.h"
#include <EngineCore/Collision.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Game_Core.h"
#include "Packets.h"
#include "EngineBase/EngineTime.h"

AOtherUI::AOtherUI()
{
	//UEngineTime Time;
	//MapTime_MilliSecond = Time.GetCurTime().MilliSecond;
	//MapTime_Second = Time.GetCurTime().Second;
}

AOtherUI::~AOtherUI()
{
}

void AOtherUI::BeginPlay()
{
	AMapUI::BeginPlay();

	//Sub_MilliSecond = MapTime_MilliSecond - MapTime_MilliSecond;
	//Sub_Second = MapTime_Second - MapTime_Second;
	//SerVer_Send = true;
}

void AOtherUI::Tick(float _DeltaTime)
{
	AMapUI::Tick(_DeltaTime);
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
		case UIPacket:
		{
			std::shared_ptr<UUIUpdatePacket> UpdatePacket = std::dynamic_pointer_cast<UUIUpdatePacket>(Protocol);
			
			//서버에서 클라에게 신호받기
			if (check == false)
			{
				Client_Send = UpdatePacket->ClientCreate;
				if (Client_Send == true)
				{			
					check = true;
				}
			}

			//클라에서 서버에게 신호받기
			if (check == false)
			{
				SerVer_Send = UpdatePacket->SerVerSend;
				if (UpdatePacket->SerVerSend == false)
				{
					ServerMapTime_Second = UpdatePacket->Second_Tens;
					Sub_Second = MapTime_Second - ServerMapTime_Second;
					SerVer_Send = true;
					check = true;
				}
			}

			break;
		}
		default:
			break;
		}
	} while (nullptr != Protocol);



}



