#pragma once

#include <EngineCore/EngineDebugMsgWindow.h>

class ContentsMainDebugWin : public UEngineDebugMsgWindow
{
	GENERATED_BODY(UEngineDebugMsgWindow);
public:
	// constrcuter destructer
	ContentsMainDebugWin(); // 디폴트 생성자
	~ContentsMainDebugWin(); // 디폴트 소멸자

	// delete Function
	ContentsMainDebugWin(const ContentsMainDebugWin& _Other) = delete; // 디폴트 복사 생성자
	ContentsMainDebugWin(ContentsMainDebugWin&& _Other) noexcept = delete; 
	ContentsMainDebugWin& operator=(const ContentsMainDebugWin& _Other) = delete; // 디폴트 대입 연산자
	ContentsMainDebugWin& operator=(ContentsMainDebugWin&& _Other) noexcept = delete;

protected:
	void Init() override;
	void OnGui(ULevel* Level, float _Delta) override;
private:
};

