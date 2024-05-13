#pragma once

#include <EngineCore/EngineDebugMsgWindow.h>

class UContentsDebugWindow : public UEngineDebugMsgWindow
{
	GENERATED_BODY(UEngineDebugMsgWindow);
public:
	// constrcuter destructer
	UContentsDebugWindow(); // 디폴트 생성자
	~UContentsDebugWindow(); // 디폴트 소멸자

	// delete Function
	UContentsDebugWindow(const UContentsDebugWindow& _Other) = delete; // 디폴트 복사 생성자
	UContentsDebugWindow(UContentsDebugWindow&& _Other) noexcept = delete;
	UContentsDebugWindow& operator=(const UContentsDebugWindow& _Other) = delete; // 디폴트 대입 연산자
	UContentsDebugWindow& operator=(UContentsDebugWindow&& _Other) noexcept = delete;

protected:
	void Init() override;
	void OnGui(ULevel* Level, float _Delta) override;
private:
};

