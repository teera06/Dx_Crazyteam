#include "PreCompile.h"
#include "MapDebugGUI.h"

std::vector<std::string> UMapDebugGUI::Msg;

UMapDebugGUI::UMapDebugGUI()
{
}

UMapDebugGUI::~UMapDebugGUI()
{
}

void UMapDebugGUI::PushMsg(std::string_view _Msg)
{
	Msg.push_back(_Msg.data());
}

void UMapDebugGUI::OnGui(ULevel* Level, float _Delta)
{
	for (size_t i = 0; i < Msg.size(); i++)
	{
		ImGui::Text(Msg[i].c_str());
	}

	Msg.clear();
}
