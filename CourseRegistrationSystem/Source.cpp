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

void inline updateSemesterResult(std::string sem) {// this really hard :(( i hope it work
	Filelist* Courses = TakeFileInFolder(sem);
	int n = CountFile(Courses);
	for (int i = 0; i < n; i++) {
		if (Courses->filename.length() > 5 && Courses->filename.compare(Courses->filename.length() - 5, 5, "Score") == 0) { DeleteCurFileList(Courses); i -= 1; n -= 1; }
		else Courses = Courses->pNext;
	}

	for (int i = 0; i < n; i++) { // ok, time to update :<
		Course* temp = BinToCourse(sem + "\\" + Courses->filename);
		for (int j = 0; j < temp->numberofstudent; j++) {
			Student* stu = BinToStu(GetFilePath(temp->stuID[j]));

			//take the idCourse to the last
			int m = _msize(stu->coursenow) / sizeof(stu->coursenow);
			for (int i = 0; i < m; i++) {
				if (strncmp(stu->coursenow[i], temp->ID, sizeof(temp->ID)) == 0) {
					char* swap = stu->coursenow[i];
					stu->coursenow[i] = stu->coursenow[m - 1];
					stu->coursenow[m - 1] = swap;
					break;
				}
			}
			m -= 1;

			Score* score=nullptr; // load score of this student here. but just need the total
			delete[] score->name;// btw it not neccessary
			int n = 0;
			if (stu->allcourse != nullptr) n = _msize(stu->allcourse) / sizeof(stu->allcourse);
			n += 1;
			//just keep;
			char** his = stu->allcourse;
			stu->allcourse = new char* [n];
			for (int i = 0; i < n - 1; i++) {
				stu->allcourse[i] = his[i];
			}
			stu->allcourse[n - 1] = stu->coursenow[m];

			delete[] his; //detele the poiter point to data, not the data
			his = stu->coursenow;
			if (m > 0) stu->coursenow = new char* [m];
			for (int i = 0; i < m; i++) {
				stu->coursenow[i] = his[i];
			}
			delete[] his;

			//update Score :((
			stu->GPA = ((stu->GPA * (float(n) - 1)) + score->totals) / float(n); // Old GPA*number of olD Subject + this Course score and / for numberof subect
			StuToBin(stu, GetFilePath(stu->ID));
			deleteStu(stu);
		}
		deleteCourse(temp);
		Courses = Courses->pNext;
	}
}

int secondrun() {
	std::fstream file("currentsem", std::fstream::in);
	if (!file) return -1;// not in time of any semester
	int year, sem;
	file.read((char*)&year, sizeof(int));
	file.read((char*)&sem, sizeof(int));
	Date start, end;
	file.close();
	file.open("Data\\SchoolYear\\" + std::to_string(year) + "\\time", std::fstream::in);
	for (int i = 0; i < sem; i++) {
		file.read((char*)&start, sizeof(Date));
		file.read((char*)&end, sizeof(Date));
	}
	if (GetTime() < start) return -1;// not in time so can't do anything
	if (GetTime() > end) {
		// load all student and update them score;
		updateSemesterResult("Data\\SchoolYear\\" + std::to_string(year) + "\\Semester" + std::to_string(sem));

		_wremove(L"currentsem");
		return 1; // this end of semester so remove file, file not exits now so it can't change anything too;
	}
	return 0;// can change score and somthing just like this of any thing of Course
}

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
	else {//end register // save new score file and made current time semester to update file.
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
		file.open("currentsem", std::fstream::out);
		file.write((char*)&year, sizeof(int));
		file.write((char*)&sem, sizeof(int));
		file.close();
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
