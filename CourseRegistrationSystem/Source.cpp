#include <windows.h>
#include<iostream>
#include<vector>
#include<string>
#include"CommonFunc.h"

void main()
{
	
	wchar_t** k = new wchar_t* [4];
	k[0] = new wchar_t[10]{ L"Nhìn" };
	k[1] = new wchar_t[10]{ L"Vô" };
	k[2] = new wchar_t[10]{ L"Đây" };
	k[3] = new wchar_t[10]{ L"Này" };
	Menu(k, 10, 10, BLUE  , RED);
}