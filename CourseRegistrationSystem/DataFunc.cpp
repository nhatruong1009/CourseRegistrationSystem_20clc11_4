#include"Data.h"
#include"CommonFunc.h"
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
	wchar_t* temp = nullptr;
	int beg = str.find(L',', 0) + 1;
	int end = str.find(L',', beg);

	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	_LText();
	stu.ID = StringToInt(temp);
	stu.account.username = new char[end - beg + 1];
	stu.account.username[end - beg] = L'\0';
	LStrToStr(stu.account.username, end - beg, temp);
	delete[] temp;

	beg = end + 1;
	end = str.find(L',', beg);
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

	beg = end + 1;
	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
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
void AddStudent(_Student*& studentlist, Student student) {
	if (studentlist == nullptr) { studentlist = new _Student{ student }; studentlist->pNext = studentlist, studentlist->pPrev = studentlist; return; }
	studentlist->pPrev = new _Student{ student,studentlist,studentlist->pPrev };
	studentlist->pPrev->pPrev->pNext = studentlist->pPrev;
}
_Student* FileInStudent(std::string filename) {
	_LText();
	std::wfstream fi(filename, std::wfstream::in);
	if (!fi) { return nullptr; }
	fi.imbue(std::locale(fi.getloc(), new std::codecvt_utf8<wchar_t>));
	_Student* stu = nullptr;
	std::wstring temp;
	while (fi)
	{
		std::getline(fi, temp);
		if (temp.length() != 0) AddStudent(stu, StringToStudent(temp));
	}
	_SText();
	return stu;
}
void FileOutStudent(_Student* stu, std::string fileout) {
	std::wfstream fo(fileout, std::wfstream::out);
	_LText();
	fo << L"﻿";
	fo.imbue(std::locale(fo.getloc(), new std::codecvt_utf8<wchar_t>));
	_Student* temp = stu;
	do
	{
		fo << stu->student.ID << L',' << stu->student.firstname << L',' << stu->student.lastname << L',' << stu->student.gender << L',' << stu->student.birth << L',' << stu->student.SocialID << L'\n';
		stu = stu->pNext;
	} while (stu != temp);
	fo.close();
}
void StuToBin(_Student* stu, std::string fileout) {
	if (stu == nullptr) return;
	std::fstream fo(fileout, std::fstream::out | std::fstream::binary);
	_Student* temp = stu;
	int k = 0;
	do {
		fo.write((char*)&stu->student.ID, sizeof(__int64));

		k = wcslen(stu->student.firstname) + 1;
		fo.write((char*)&k, sizeof(int));
		fo.write((char*)&*stu->student.firstname, k * 2);

		k = wcslen(stu->student.lastname) + 1;
		fo.write((char*)&k, sizeof(int));
		fo.write((char*)&*stu->student.lastname, k * 2);

		fo.write(&stu->student.gender, 1);

		fo.write((char*)&stu->student.birth, sizeof(Date));

		fo.write((char*)&stu->student.SocialID, sizeof(__int64));

		if (stu->student.coursenow == nullptr) k = 0;
		else k = _msize(stu->student.coursenow) / sizeof(char*);
		fo.write((char*)&k, sizeof(int));
		for (int i = 0; i < k; i++) {
			int e = strlen(stu->student.coursenow[i]) + 1;
			fo.write((char*)&e, sizeof(int));
			fo.write(stu->student.coursenow[i], e);
		}

		if (stu->student.allcourse == nullptr) k = 0;
		else k = _msize(stu->student.allcourse) / sizeof(char*);
		fo.write((char*)&k, sizeof(int));
		for (int i = 0; i < k; i++) {
			int e = strlen(stu->student.allcourse[i]) + 1;
			fo.write((char*)&e, sizeof(int));
			fo.write(stu->student.allcourse[i], e);
		}

		k = strlen(stu->student.account.username) + 1;
		fo.write((char*)&k, sizeof(int));
		fo.write(stu->student.account.username, k);

		k = strlen(stu->student.account.password) + 1;
		fo.write((char*)&k, sizeof(int));
		fo.write(stu->student.account.password, k);
		
		fo.write((char*)&stu->student.GPA, sizeof(float));

		stu = stu->pNext;
	} while (stu != temp);
	fo.close();
}
void BinToStu(_Student*& stu, std::string filein) {
	std::fstream fi(filein, std::fstream::in | std::fstream::binary);
	if (!fi) return;
	_LText();
	fi.seekg(-1, std::ios_base::end);
	int l = fi.tellp();
	fi.seekg(0, std::ios_base::beg);
	int k = 0;
	Student temp;
	while(fi.tellp()<l){
		fi.read((char*)&temp.ID, sizeof(__int64));

		fi.read((char*)&k, sizeof(int));
		temp.firstname = new wchar_t[k];
		fi.read((char*)&temp.firstname[0], k * 2);

		fi.read((char*)&k, sizeof(int));
		temp.lastname = new wchar_t[k];
		fi.read((char*)&temp.lastname[0], k * 2);

		fi.read(&temp.gender, 1);

		fi.read((char*)&temp.birth, sizeof(Date));

		fi.read((char*)&temp.SocialID, sizeof(__int64));

		fi.read((char*)&k, sizeof(int));
		if (k != 0) temp.coursenow = new char* [k];
		for (int i = 0; i < k; i++) {
			int e=0;
			fi.write((char*)&e, sizeof(int));
			if (e != 0) temp.coursenow[i] = new char[e];
			fi.write(temp.coursenow[i], e);
		}

		fi.read((char*)&k, sizeof(int));
		if (k != 0) temp.allcourse = new char* [k];
		for (int i = 0; i < k; i++) {
			int e = 0;
			fi.write((char*)&e, sizeof(int));
			if (e != 0) temp.allcourse[i] = new char[e];
			fi.write(temp.allcourse[i], e);
		}

		fi.read((char*)&k, sizeof(int));
		temp.account.username = new char[k];
		fi.read(temp.account.username, k);

		fi.read((char*)&k, sizeof(int));
		temp.account.password = new char[k];
		fi.read(temp.account.password, k);

		fi.read((char*)&temp.GPA, sizeof(float));
		
		AddStudent(stu, temp);
	}
	fi.close();
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
	std::wcout << a->firstname << "\t";
	std::wcout << a->lastname << "\t";
	std::wcout << a->gender << '\t';
	std::wcout << a->birth << '\t';
	std::wcout << a->SocialID << '\t';
	std::wcout << a->account.username << '\t';
	std::wcout << a->account.password << '\n';
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
Student* FindStudent(_Student* studentlist, unsigned __int64 ID) {
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
void RemoveStudent(_Student*& studentlist, unsigned __int64 ID) {
	if (studentlist == nullptr) return;
	_Student* temp = studentlist;
	_Student* pcur = studentlist;
	while (pcur->student.ID != ID && pcur->pNext != temp)
	{
		pcur = pcur->pNext;
	}
	if (studentlist->student.ID != ID) return;
	if (pcur->pNext = pcur) studentlist = nullptr;
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

void ClassToBin(_Class *cls,std::string filename){
	if (cls == nullptr) return;
	std::fstream fo(filename, std::fstream::out | std::fstream::binary);
	_Class* temp = cls;
	int k;
	do {
		k = strlen(cls->classes.name) + 1;
		fo.write((char*)&k, sizeof(int));
		fo.write((char*)&cls->classes.name, k);
		if (cls->classes.student == nullptr) k = 0;
		else k = _msize(cls->classes.student) / sizeof(_Student*);
		fo.write((char*)&k, sizeof(int));
		for (int i = 0; i < k; i++) {

		}
		
	} while (cls != temp);
}

void SchoolYearToBin(SchoolYear sch) {
	char* year = NumToStr(sch.year);
	StrCat(year, 8, "save.bin");
	std::fstream fo(year, std::fstream::out | std::fstream::binary);
	fo.write((char*)&sch.year, sizeof(int));
	int k = 0;

}