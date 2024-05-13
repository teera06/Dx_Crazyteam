#pragma once
#include <EngineCore/EngineEditorWindow.h>

class UMapDebugGUI : public UEngineEditorWindow
{
public :
	// constrcuter destructer
	UMapDebugGUI();
	~UMapDebugGUI();

	// delete Function
	UMapDebugGUI(const UMapDebugGUI& _Other) = delete;
	UMapDebugGUI(UMapDebugGUI&& _Other) noexcept = delete;
	UMapDebugGUI& operator=(const UMapDebugGUI& _Other) = delete;
	UMapDebugGUI& operator=(UMapDebugGUI&& _Other) noexcept = delete;

	static void PushMsg(std::string_view _Msg);

protected:
	void OnGui(ULevel* Level, float _Delta) override;

private :
	static std::vector<std::string> Msg;
};

