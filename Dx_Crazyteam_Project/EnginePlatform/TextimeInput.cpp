#include "PreCompile.h"
#include "TextimeInput.h"

#include <EnginePlatform/EngineInput.h>

#pragma warning(disable:4996) 

char UTextimeInput::Text[255]="";
char UTextimeInput::Cstr[10]="";
bool UTextimeInput::OnOff = true;
bool UTextimeInput::bHangeul=false;
HWND UTextimeInput::hwnd;
HIMC UTextimeInput::himc;


std::string UTextimeInput::GetReadText()
{
	std::string ch=Text;

	return ch +Cstr;
}

void UTextimeInput::On()
{
	OnOff = true;
}

void UTextimeInput::Off()
{
	OnOff = false;
}



void UTextimeInput::SetIme(HWND _hWnd,UINT _msg, WPARAM _wparam, LPARAM _lParam)
{

	if (false == OnOff)
	{
		return;
	}

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




