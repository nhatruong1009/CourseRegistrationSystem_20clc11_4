#include <windows.h>
#include<iostream>
#include<vector>
#include<string>
#include"CommonFunc.h"

using namespace std;
void main()
{	
	Filelist* a = TakeFileInFolder("Data");
	Filelist* temp = a;
	_LText();
	do {
		wcout << a->filename << '\n';
		a = a->pNext;
	} while (a != temp);
}