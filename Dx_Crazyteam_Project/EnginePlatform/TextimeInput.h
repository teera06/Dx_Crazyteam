#pragma once

class UEngineWindow;
class UTextimeInput
{
	friend UEngineWindow;
public:

	static void IMEInput();
	static std::string GetReadText();


protected:
private:
	

	static std::string ReadText;
	static std::string ComstrText;
	static std::string MidText;

	static bool bHangeul;
	static HWND hwnd;
	static HIMC himc;
	static void SetIme(HWND _hWnd, UINT _msg, WPARAM _wparam, LPARAM _lParam);
	static void SetNativeMode(bool bHangeul);
};

