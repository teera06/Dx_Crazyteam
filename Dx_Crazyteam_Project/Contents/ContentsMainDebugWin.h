#pragma once

#include <EngineCore/EngineDebugMsgWindow.h>

class UContentsMainDebugWin : public UEngineDebugMsgWindow
{
	GENERATED_BODY(UEngineDebugMsgWindow);
public:
	// constrcuter destructer
	UContentsMainDebugWin(); // 디폴트 생성자
	~UContentsMainDebugWin(); // 디폴트 소멸자

	// delete Function
	UContentsMainDebugWin(const UContentsMainDebugWin& _Other) = delete; // 디폴트 복사 생성자
	UContentsMainDebugWin(UContentsMainDebugWin&& _Other) noexcept = delete; 
	UContentsMainDebugWin& operator=(const UContentsMainDebugWin& _Other) = delete; // 디폴트 대입 연산자
	UContentsMainDebugWin& operator=(UContentsMainDebugWin&& _Other) noexcept = delete;

	static void SetIsLevel(bool _IsLevel)
	{
		IsLevel = _IsLevel;
	}


protected:
	void Init() override;
	void OnGui(ULevel* Level, float _Delta) override;
private:

	static bool IsLevel;
};

