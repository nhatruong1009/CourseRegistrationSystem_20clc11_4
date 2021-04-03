#include"Data.h"
#include"CommonFunc.h"
#include<string>
<<<<<<< Updated upstream
=======
#include<fstream>
>>>>>>> Stashed changes
#include<locale>
#include<codecvt>
std::ostream& operator<<(std::ostream& os, const Date& dt)
{
	os << dt.dd << '/' << dt.mm << '/' << dt.yy;
	return os;
}
std::wostream& operator<<(std::wostream& os, const Date& dt)
{
	os << dt.dd << '/' << dt.mm << '/' << dt.yy;
	return os;
}
std::wostream& operator<<(std::wostream& os, const tm& t) {
	os << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << " " << t.tm_mday << "/" << t.tm_mon << "/" << t.tm_year;
	return os;
}

Student StringToStudent(std::wstring str) {
	//No, Student ID, First name, Last name, Gender, Date of Birth, Social ID
	Student stu;
<<<<<<< Updated upstream
	wchar_t* temp = nullptr;
	int beg = str.find(L',', 0) + 1;
	int end = str.find(L',', beg);

	temp = new wchar_t[end - beg +1];
	temp[end - beg]=L'\0';
	str.copy(temp, end - beg, beg);
	_LText();
	stu.ID = StringToInt(temp);
	stu.account.username = new char[end - beg + 1];
	stu.account.username[end - beg];
	LStrToStr(stu.account.username, end - beg, temp);
=======
	int beg = 0, end = 0;
	wchar_t* temp;
	beg = str.find(L',', 0) + 1;

	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg ] = L'\0';
	str.copy(temp, end - beg , beg);
	stu.ID = StringToInt(temp);
	stu.account.username = new char[wcslen(temp) + 1];
	stu.account.username[wcslen(temp)] = '\0';
	LStrToStr(stu.account.username, wcslen(temp), temp);
>>>>>>> Stashed changes
	delete[] temp;

	beg = end + 1;
	end = str.find(L',', beg);
<<<<<<< Updated upstream
	stu.firstname = new wchar_t[end - beg + 1];
	stu.firstname[end - beg] = L'\0';
	str.copy(stu.firstname, end - beg, beg);

	beg = end + 1;
	end = str.find(L',', beg);
	stu.lastname = new wchar_t[end - beg + 1];
	stu.lastname[end - beg] = L'\0';
	str.copy(stu.lastname, end - beg, beg);

	beg = end + 1;
	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	if (wcscmp(temp, L"Nam") == 0)stu.gender = 'M';
	else stu.gender = 'W';
	delete[] temp;
=======
	temp = new wchar_t[end - beg + 1];
	temp[end - beg ] = L'\0';
	str.copy(temp, end - beg, beg);
	stu.firstname = temp;
>>>>>>> Stashed changes

	beg = end + 1;
	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
<<<<<<< Updated upstream
	stu.birth = StringToDate(temp);
	delete[] temp;


	beg = end + 1;
	end = str.length();
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	stu.SocialID = StringToInt(temp);
	delete[] temp;

	stu.account.password = new char[7]{ "123456" };
	return stu;
}
=======
	stu.lastname = temp;

	beg = end + 1;
	end = str.find(L',',beg);
	str.copy((wchar_t*)&stu.gender, 1, beg);
>>>>>>> Stashed changes

	beg = end + 1;
	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg ] = L'\0';
	str.copy(temp, end - beg, beg);
	stu.birth = StringToDate(temp);
	delete[] temp;

	beg = end + 1;
	temp = new wchar_t[str.length() - beg + 1];
	temp[str.length() - beg] = L'\0';
	str.copy(temp, str.length() - beg , beg);
	stu.SocialID = StringToInt(temp);
	delete[] temp;

	stu.account.password = new char[7]{ "123456" };

	return stu;
}
void AddStudent(_Student*& studentlist, Student student) {
	if (studentlist == nullptr) { studentlist = new _Student{ student }; studentlist->pNext = studentlist, studentlist->pPrev = studentlist; return; }
	studentlist->pPrev = new _Student{ student,studentlist,studentlist->pPrev };
	studentlist->pPrev->pPrev->pNext = studentlist->pPrev;
}
<<<<<<< Updated upstream

_Student* FileInStudent(std::string filename) {
	std::wfstream fi(filename, std::wfstream::in);
	if (!fi) { return nullptr; }
	fi.imbue(std::locale(fi.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	_Student* stu = nullptr;
	std::wstring temp;
	while (fi)
	{
		std::getline(fi, temp);
		if (temp.length() != 0) AddStudent(stu, StringToStudent(temp));
	}
	return stu;
}

void FileOutStudent(_Student* stu, std::string fileout) {
	std::wfstream fo(fileout, std::wfstream::out);
	fo << L"﻿";
=======
_Student* StudentFileIn(std::string filename) {
	std::wfstream fi(filename, std::wfstream::in);
	if (!fi) { return nullptr; }
	fi.imbue(std::locale(fi.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	_Student* result=nullptr;
	while (fi)
	{
		std::wstring temp;
		std::getline(fi, temp);
		if (temp.length() != 0) AddStudent(result, StringToStudent(temp));
	}
	return result;
}
void StudentFileOut(_Student* stu, std::string fileout) {
	std::wfstream fo(fileout, std::wfstream::out);
	fo<< L"﻿";
>>>>>>> Stashed changes
	fo.imbue(std::locale(fo.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	_Student* temp = stu;
	do
	{
		fo << stu->student.ID << ',' << stu->student.firstname << ',' << stu->student.lastname << ',' << stu->student.gender << ',' << stu->student.birth << ',' << stu->student.SocialID << '\n';
		stu = stu->pNext;
	} while (stu != temp);
	fo.close();
}
int NumberOfStudent(_Student* stu) {
	if (stu == nullptr) return 0;
	int k = 0;
	_Student* temp = stu;
	do {
		k += 1;
		stu = stu->pNext;
	} while (stu != temp);
	return k;
}
void PrintStu(Student* a) {
	if (a == nullptr) return;
	_LText();
	std::wcout << a->ID << "  ";
	//std::wcout << a->firstname << "\t";
	//std::wcout << a->lastname << "\t";
	std::wcout << a->gender << '\t';
	std::wcout << a->birth << '\t';
	std::wcout << a->SocialID << '\n';
	//std::wcout << a->account.username << '\t';
	//std::wcout << a->account.password << '\n';
	_SText();
}
void PrintStu(_Student* stu) {
	if (stu == nullptr) return;
	_Student* temp = stu;
	do
	{
		PrintStu(&stu->student);
		stu = stu->pNext;
	} while (stu != temp);
}
Student* FindStudent(_Student* studentlist, unsigned __int32 ID) {
	if (studentlist == nullptr) return nullptr;
	_Student* temp = studentlist;
	while (studentlist->student.ID != ID && studentlist->pNext != temp)
	{
		studentlist = studentlist->pNext;
	}
	if (studentlist->student.ID != ID) { return nullptr; }
	return &studentlist->student;
}
void DealloStu(_Student*& stu) {
	if (stu == nullptr) return;
	_Student* temp = stu;
	do {
		_Student* a = stu;
		stu = stu->pNext;
		delete a;
	} while (stu != temp);
}
void RemoveStudent(_Student*& studentlist, unsigned __int32 ID) {
	if (studentlist == nullptr) return;
	_Student* temp = studentlist;
	_Student* pcur = studentlist;
	while (pcur->student.ID != ID && pcur->pNext != temp)
	{
		pcur = pcur->pNext;
	}
	if (studentlist->student.ID != ID) return;
	if (pcur->pNext = pcur) studentlist = nullptr;
	else if (pcur == studentlist) studentlist = studentlist->pNext;
	pcur->pPrev->pNext = pcur->pNext;
	pcur->pNext->pPrev = pcur->pPrev;
	delete pcur;
}
_Student* ConnectStudent(_Student*& a, _Student*& b) {
	if (a == nullptr) {
		_Student* temp = b; b = nullptr; return temp;
	}
	if (b == nullptr) {
		_Student* temp = a; a = nullptr; return temp;
	}
	a->pPrev->pNext = b;
	b->pPrev->pNext = a;
	_Student* temp = a->pPrev;
	a->pPrev = b->pPrev;
	b->pPrev = temp;
	a = nullptr;
	b = nullptr;
	return temp->pNext;
}

void StuSaveToBin(_Student*stu, std::string filename) {
	std::fstream fo(filename, std::fstream::out | std::fstream::binary);
	if (stu == nullptr) { fo.close(); return; }
	int temp = 0;
	_Student* k = stu;
	do
	{
		fo.write((char*)&stu->student.ID, sizeof(__int64));

		temp = wcslen(stu->student.firstname) + 1;
		fo.write((char*)&temp, sizeof(int));
		fo.write((char*)&stu->student.firstname, temp * 2);

		temp = wcslen(stu->student.lastname) + 1;
		fo.write((char*)&temp, sizeof(int));
		fo.write((char*)&stu->student.lastname, temp * 2);

		fo.write(&stu->student.gender, 1);

		fo.write((char*)&stu->student.birth, sizeof(Date));

		fo.write((char*)&stu->student.SocialID, sizeof(__int64));
	
		if (stu->student.coursenow == nullptr)
			temp = 0;
		else temp = _msize(stu->student.coursenow) / sizeof(char*);
		fo.write((char*)&temp, sizeof(int));
		for (int i = 0; i < temp; i++) {
			int temp2 = strlen(stu->student.coursenow[i]) + 1;
			fo.write((char*)&temp2, sizeof(int));
			fo.write(stu->student.coursenow[i], temp2);
		}

		if (stu->student.coursenow == nullptr)
			temp = 0;
		else temp = _msize(stu->student.allcourse) / sizeof(char*);
		fo.write((char*)&temp, sizeof(int));
		for (int i = 0; i < temp; i++) {
			int temp2 = strlen(stu->student.allcourse[i]) + 1;
			fo.write((char*)&temp2, sizeof(int));
			fo.write(stu->student.allcourse[i], temp2);
		}

		temp = strlen(stu->student.account.username) + 1;
		fo.write((char*)&temp, sizeof(int));
		fo.write((char*)&stu->student.account.username, temp);

		temp = strlen(stu->student.account.password) + 1;
		fo.write((char*)&temp, sizeof(int));
		fo.write((char*)&stu->student.account.password, temp);

		fo.write((char*)&stu->student.GPA, sizeof(float));
		
		stu = stu->pNext;
	} while (stu != k);
	fo.close();
}

_Student* BinToStu(std::string filename) {
	std::fstream fi(filename, std::fstream::in | std::fstream::binary);
	if (!fi) { return nullptr; }
	Student stu;
	_Student* list = nullptr;
	int temp = 0;
	while (fi)
	{
		fi.read((char*)&stu.ID, sizeof(__int64));

		fi.read((char*)&temp, sizeof(int));
		stu.firstname = new wchar_t[temp];
		fi.read((char*)&stu.firstname, temp * 2);


		fi.read((char*)&temp, sizeof(int));
		stu.lastname = new wchar_t[temp];
		fi.read((char*)&stu.lastname, temp * 2);

		fi.read(&stu.gender, 1);

		fi.read((char*)&stu.birth, sizeof(Date));

		fi.read((char*)&stu.SocialID, sizeof(__int64));

		fi.read((char*)&temp, sizeof(int));
		stu.coursenow = new char* [temp];
		for (int i = 0; i < temp; i++) {
			int temp2=0;
			fi.read((char*)&temp2, sizeof(int));
			stu.coursenow[i] = new char[temp2];
			fi.read(stu.coursenow[i], temp2);
		}

		fi.read((char*)&temp, sizeof(int));
		stu.allcourse = new char* [temp];
		for (int i = 0; i < temp; i++) {
			int temp2=0;
			fi.read((char*)&temp2, sizeof(int));
			stu.allcourse[i] = new char[temp2];
			fi.read(stu.allcourse[i], temp2);
		}

		fi.read((char*)&temp, sizeof(int));
		stu.account.username = new char[temp];
		fi.read((char*)&stu.account.username, temp);

		fi.read((char*)&temp, sizeof(int));
		stu.account.password = new char[temp];
		fi.read((char*)&stu.account.password, temp);

		fi.read((char*)&stu.GPA, sizeof(float));
		PrintStu(&stu);
		AddStudent(list, stu);
	}

	return list;
}