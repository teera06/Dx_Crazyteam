#include "PreCompile.h"
#include "TextimeInput.h"

#include <EnginePlatform/EngineInput.h>

#pragma warning(disable:4996) 

std::string UTextimeInput::ReadText ="";
std::string UTextimeInput::MidText = "";
std::string UTextimeInput::ComstrText="";
char UTextimeInput::Text[255]="";
char UTextimeInput::Cstr[10]="";
bool UTextimeInput::bHangeul=false;
HWND UTextimeInput::hwnd;
HIMC UTextimeInput::himc;

void UTextimeInput::IMEInput()
{
	if (true == UEngineInput::IsDown(VK_BACK))
	{
		if (ReadText.size() >0)
		{
			ReadText.pop_back();
		}
		return;
	}

	if (true == UEngineInput::IsDown(VK_SPACE))
	{
		ReadText += " ";
		return;
	}

	if (true == UEngineInput::IsDown(VK_TAB))
	{
		if (false == bHangeul)
		{
			bHangeul = true;
		}
		else
		{
			bHangeul = false;
		}
		SetNativeMode(bHangeul);
		return;
	}

	for (int i = '0'; i <= '9'; i++)
	{
		if (true == UEngineInput::IsDown(i))
		{
			ReadText += static_cast<char>(i);
			return;
		}
	}

	if (false == bHangeul)
	{
		return;
	}

	for (int i = 'A'; i <= 'Z'; i++)
	{
		if (true == UEngineInput::IsDown(i))
		{
			ReadText += tolower(static_cast<char>(i));
			return;
		}
	}
}

std::string UTextimeInput::GetReadText()
{
	std::string ch=Text;

	return ch +Cstr;
}



void UTextimeInput::SetIme(HWND _hWnd,UINT _msg, WPARAM _wparam, LPARAM _lParam)
{
	hwnd = _hWnd;
	himc = ImmGetContext(_hWnd);

	int len = 0;
	switch (_msg)
	{
	case WM_IME_COMPOSITION:
		if (_lParam & GCS_COMPSTR) // 조합중 글자 
		{
			len = ImmGetCompositionString(himc, GCS_COMPSTR, NULL, 0);
			ImmGetCompositionString(himc, GCS_COMPSTR, Cstr, len);
			Cstr[len] = 0;
			
		}else if(_lParam & GCS_RESULTSTR) // 완성중 글자
		{
			len = ImmGetCompositionString(himc, GCS_RESULTSTR, NULL, 0);
		
			if (len > 0)
			{
				ImmGetCompositionString(himc, GCS_RESULTSTR, Cstr, len);
				Cstr[len] = 0;
				strcpy(Text + strlen(Text), Cstr);
				memset(Cstr, 0, 10);
			}
			
		}
		bHangeul = true;
		ImmReleaseContext(hwnd, himc); 
		break;
	case WM_CHAR: // 영어랑 숫자 처리
		if (_wparam == 8)
		{
			if (strlen(Text) > 0 && true == bHangeul) // 한글 지울때 
			{
				if (' ' == Text[strlen(Text) - 1]) // 스페이스바 빈공간 해결
				{
					Text[strlen(Text) - 1] = 0;
				}

				Text[strlen(Text) - 1] = 0;

				if (strlen(Text) > 0)
				{
					Text[strlen(Text) - 1] = 0;
				}
			}
			else if(strlen(Text) > 0 && false == bHangeul) // 영어 지울때
			{
				Text[strlen(Text) - 1] = 0;
			}
		}
		else
		{
			if (_wparam == VK_SPACE)
			{
				bHangeul = true;
			}
			else
			{
				bHangeul = false;
			}

			if (_wparam == VK_RETURN)
			{
				break;
			}
			len = static_cast<int>(strlen(Text));
			Text[len] = _wparam & 0xff;
		}
		break;
	case WM_KEYDOWN:
		if (_wparam == VK_SPACE)
		{
			bHangeul = true;
		}
		break;
	default:
		break;
	}
}

void UTextimeInput::SetNativeMode(bool bHangeul)
{
	DWORD dwConv, dwSent;

	DWORD dwTemp;



	ImmGetConversionStatus(himc, &dwConv, &dwSent);

	dwTemp = dwConv & ~IME_CMODE_LANGUAGE;

	if (bHangeul) {

		dwTemp |= IME_CMODE_NATIVE;

	}
	else {

		dwTemp |= IME_CMODE_ALPHANUMERIC;

	}

	dwConv = dwTemp;

	ImmSetConversionStatus(himc, dwConv, dwSent);

	ImmReleaseContext(hwnd, himc);
}


