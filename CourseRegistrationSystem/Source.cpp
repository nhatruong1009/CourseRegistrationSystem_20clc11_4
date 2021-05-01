#include <windows.h>
#include<iostream>
#include<vector>
#include<string>
#include"CommonFunc.h"
#include"menu.h"
#include <cstdint>
#include <filesystem>
#include"Data.h"

int fistrun(std::string&current) {
	current = "";
	std::fstream file("fistrun", std::fstream::in | std::ios::binary);
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
		current = "Data\\SchoolYear" + std::to_string(year) + "\\Semester" + std::to_string(sem);
		return 1;// can register
	}
	else {//end register
		std::string temp= "Data\\SchoolYear" + std::to_string(year) + "\\Semester" + std::to_string(sem);
		Filelist* filelist = TakeFileInFolder(temp);
		int n = CountFile(filelist);
		for (int i = 0; i < n; i++) {
			Course* cour = BinToCourse(temp + "\\" + filelist->filename);
			for (int m = 0; m < cour->numberofstudent; m++) {
				for (int n = m + 1; n < cour->numberofstudent; n++) {
					if (cour->stuID[m] > cour->stuID[n]) {
						unsigned __int64 k = cour->stuID[m];
						cour->stuID[m] = cour->stuID[n];
						cour->stuID[n] = k;
					}
				}
			}
			CourseToBin(cour, filelist->filename, temp);
			std::ofstream filetemp(temp + "\\" + filelist->filename + "Score");
			filetemp.close();
		}
		file.close();
		_wrmdir(L"fistrun");
		return 2;
	}
}

void main()
{
	//int a = InputNumber();
	//std::cout << '\t' << a;
	//Student* test = BinToStu("Data\\Grade\\K2020\\Student\\20127376");
	std::string current;
	fistrun(current);
	userTypeMode();
	//std::cout << SearchCurrent();
	//std::cout << "dada";
}
