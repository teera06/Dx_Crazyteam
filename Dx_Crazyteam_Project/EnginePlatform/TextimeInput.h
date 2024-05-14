#pragma once
class UTextimeInput
{
public:
	// constrcuter destructer
	UTextimeInput(); // 디폴트 생성자
	~UTextimeInput(); // 디폴트 소멸자

	// delete Function
	UTextimeInput(const UTextimeInput& _Other) = delete; // 디폴트 복사 생성자
	UTextimeInput(UTextimeInput&& _Other) noexcept = delete; 
	UTextimeInput& operator=(const UTextimeInput& _Other) = delete; // 디폴트 대입 연산자
	UTextimeInput& operator=(UTextimeInput&& _Other) noexcept = delete;
	static std::function<int(HWND, UINT, WPARAM, LPARAM)> SetTextIme;
protected:

private:
	char Text[255];
	char Cstr[10];
	char CanText[200];
	int CNumber = 0;
	int CanMax = 0;

};

