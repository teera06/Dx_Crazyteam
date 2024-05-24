#pragma once

class UEngineWindow;
class UTextimeInput
{
	friend UEngineWindow;
public:
	static std::string GetReadText();
	static void On();
	static void Off();

	static bool GetOnOff()
	{
		return OnOff;
	}

	static void SetFontLen(bool _FontLen)
	{
		// FontLen true -> 챗팅용
		// false -> 닉네임 용
		FontLen = _FontLen;
	}

protected:
private:
	
	static HWND hwnd;
	static HIMC himc;

	static char Text[255];
	static char Cstr[10]; 

	static bool OnOff;
	static bool FontLen;
	static bool FontOnOff;

	static void SetIme(HWND _hWnd, UINT _msg, WPARAM _wparam, LPARAM _lParam);
	
};

