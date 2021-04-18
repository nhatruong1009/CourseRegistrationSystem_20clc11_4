#include <windows.h>
#include<iostream>
#include<vector>
#include<string>
#include"CommonFunc.h"

using namespace std;
void main()
{
	wchar_t** k = new wchar_t* [4];
	k[0] = new wchar_t[10]{ L"Trần" };
	k[1] = new wchar_t[10]{ L"Nhật" };
	k[2] = new wchar_t[10]{ L"Trường" };
	k[3] = new wchar_t[20]{ L"testcase chose" };
	Choose(k, 10, 9);
}