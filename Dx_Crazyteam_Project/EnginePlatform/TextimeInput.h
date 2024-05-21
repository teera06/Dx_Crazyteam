#pragma once

class UEngineWindow;
class UTextimeInput
{
	friend UEngineWindow;
public:
	static std::string GetReadText();
	static void On();
	static void Off();
protected:
private:
	
	static HWND hwnd;
	static HIMC himc;

	static char Text[255];
	static char Cstr[10]; 

	static bool OnOff;
	
	static void SetIme(HWND _hWnd, UINT _msg, WPARAM _wparam, LPARAM _lParam);
	
};

