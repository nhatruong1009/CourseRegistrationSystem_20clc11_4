#include <windows.h>
#include<iostream>
#include<vector>
#include<string>
#include"CommonFunc.h"
#include"menu.h"
#include <cstdint>
#include <filesystem>
#include"Data.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


int fistrun(std::string& current) {
	std::fstream file("firstrun", std::fstream::in | std::ios::binary);
	if (!file) return -1;// everything done for this semester
	int year;
	int sem;
	Date Start;
	Date End;
	file.read((char*)&year, sizeof(int));
	file.read((char*)&sem, sizeof(int));
	file.read((char*)&Start, sizeof(Date));
	file.read((char*)&End, sizeof(Date));
	Date now = GetTime();
	if (now < Start) return 0;// not in register time;
	else if (now >= Start && now <= End) {
		current = "Data\\SchoolYear\\" + std::to_string(year) + "\\Semester" + std::to_string(sem);
		return 1;// can register
	}
	else {//end register
		current= "Data\\SchoolYear\\" + std::to_string(year) + "\\Semester" + std::to_string(sem);
		Filelist* filelist = TakeFileInFolder(current);
		//std::cout << filelist->filename;
		int n = CountFile(filelist);
		for (int i = 0; i < n; i++) {
			Course* cour = BinToCourse(current + "\\" + filelist->filename);
			for (int m = 0; m < cour->numberofstudent; m++) {
				for (int n = m + 1; n < cour->numberofstudent; n++) {
					if (cour->stuID[m] > cour->stuID[n]) {
						unsigned __int64 k = cour->stuID[m];
						cour->stuID[m] = cour->stuID[n];
						cour->stuID[n] = k;
					}
				}
			}
			CourseToBin(cour, filelist->filename, current);
			SaveScore(cour, current + "\\" + filelist->filename + "Score");
			filelist = filelist->pNext;
		}
		file.close();
		_wremove(L"firstrun");
		return 2;
	}
}



void main()
{
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	//int a = InputNumber();
	//std::cout << '\t' << a;
	//Student* test = BinToStu("Data\\Grade\\K2020\\Student\\20127376");
	//
	/*Student* a = BinToStu(GetFilePath(20127303));
	std::cout << _msize(a->coursenow) / sizeof(a->coursenow);*/

	
	{
		std::cout << GetTime();
		std::string current = "";
		std::cout << fistrun(current) << " ";
		std::cout << current;
		userTypeMode();
	}
	//std::cout << SearchCurrent();
	//std::cout << "dada";
	//unsigned __int64* ID = new unsigned __int64[3];
	//ID[0] = 20127610;
	//ID[1] = 20127001;
	//ID[2] = 20127376;
	//Student** a = SearchStuArr(ID, "2020");
	//deleteStuArray(a);
	//deleteIntArray(ID);
	//


	if (_CrtDumpMemoryLeaks())
	{
		std::cout << "Leak";
	}
	else std::cout<< "No";

}
