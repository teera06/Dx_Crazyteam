#include "PreCompile.h"
#include "TextimeInput.h"

#include <EnginePlatform/EngineInput.h>

#pragma warning(disable:4996) 

char UTextimeInput::Text[50]="";
char UTextimeInput::Cstr[10]="";
char UTextimeInput::Text1[50]="";
bool UTextimeInput::OnOff = false;
bool UTextimeInput::FontLen = false;
bool UTextimeInput::FontOnOff = true;

HWND UTextimeInput::hwnd;
HIMC UTextimeInput::himc;


std::string UTextimeInput::GetReadText()
{
	//char Text1[50];
	memset(Text1, 0, 50);

	if (true == FontLen)
	{
		if (strlen(Text) >= 49)
		{
			FontOnOff = false;
			return Text;
		}

		strcpy(Text1, Text);
		

		if (Cstr[0] != 0)
		{
			strcpy(Text1 + strlen(Text), Cstr);
		}

		if (FontOnOff == true)
		{
			return Text1;
		}
	}
	else
	{
		if (strlen(Text) >= 15)
		{
			FontOnOff = false;
			return Text;
		}


		strcpy(Text1, Text);

		if (Cstr[0] != 0)
		{
			strcpy(Text1 + strlen(Text), Cstr);
		}


		if (FontOnOff == true)
		{
			return Text1;
		}

	}
	return 0;
}

void UTextimeInput::On()
{
	OnOff = true;
	FontOnOff = true;
}

void UTextimeInput::Off()
{
	OnOff = false;
	FontOnOff = false;
	memset(Text, 0, 50);
	memset(Cstr, 0, 10);
	memset(Text1, 0, 50);
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
		if (false == FontOnOff)
		{
			break;
		}

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
		ImmReleaseContext(hwnd, himc); 
		break;
	case WM_CHAR: // 영어랑 숫자 처리

		if (_wparam == 8)
		{
			FontOnOff = true;
			if (strlen(Text) > 0) // 한글 지울때 
			{
				
				if (Text[strlen(Text) - 1] == ' ')
				{
					Text[strlen(Text) - 1] = 0;
					memset(Cstr, 0, 10);
					return;
				}

				if (Text[strlen(Text) - 1] >= 33 && Text[strlen(Text) - 1] <= 126) // 아스키 코드 사용 영어랑 특수문자들 구분
				{
					Text[strlen(Text) - 1] = 0;
					memset(Cstr, 0, 10);
					return;
				}


				Text[strlen(Text) - 1] = 0;

				if (strlen(Text) > 0)
				{
					Text[strlen(Text) - 1] = 0;
				}

				memset(Cstr, 0, 10);
			}
		}
		else
		{

			if (false == FontOnOff)
			{
				break;
			}

			if (_wparam == VK_RETURN)
			{
				break;
			}
			//len = static_cast<int>(strlen(Text));
			Text[strlen(Text)] = _wparam & 0xff;
			Text[strlen(Text)] = 0;
		}
		break;
	case WM_KEYDOWN:
		if (false == FontOnOff)
		{
			break;
		}
		break;
	default:
		if (false == FontOnOff)
		{
			break;
		}
		break;
	}
}




