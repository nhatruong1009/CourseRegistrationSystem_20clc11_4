#include"Data.h"
#include"CommonFunc.h"
#include <sys/stat.h>
std::ostream& operator<<(std::ostream& os, const Date& dt)
{
	std::string temp;
	if (dt.dd < 10) temp += '0' + std::to_string(dt.dd);
	else temp += std::to_string(dt.dd);
	temp += '/';
	if (dt.mm < 10) temp += '0' + std::to_string(dt.mm);
	else temp += std::to_string(dt.mm);
	temp += '/';
	temp += std::to_string(dt.yy);
	os << temp;
	return os;
}
std::wostream& operator<<(std::wostream& os, const Date& dt)
{
	std::wstring temp;
	if (dt.dd < 10) temp += L'0' + std::to_wstring(dt.dd);
	else temp += std::to_wstring(dt.dd);
	temp += L'/';
	if (dt.mm < 10) temp += L'0' + std::to_wstring(dt.mm);
	else temp += std::to_wstring(dt.mm);
	temp += L'/';
	temp += std::to_wstring(dt.yy);
	os << temp;
	return os;
}
std::wostream& operator<<(std::wostream& os, const tm& t) {
	os << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << " " << t.tm_mday << "/" << t.tm_mon << "/" << t.tm_year;
	return os;
}

bool operator==(Date a, Date b) {
	return a.dd == b.dd && a.mm == b.mm && a.yy == b.yy;
}
bool operator<(Date a, Date b) {
	if (a.yy < b.yy) return true;
	if (a.yy > b.yy) return false;
	if (a.mm < b.mm) return true;
	if (a.mm > b.mm) return false;
	if (a.dd < b.dd) return true;
	return false;

}
bool operator<=(Date a, Date b) {
	return a == b || a < b;
}
bool operator>(Date a, Date b) {
	if (a.yy > b.yy) return true;
	if (a.yy < b.yy) return false;
	if (a.mm > b.mm) return true;
	if (a.mm < b.mm) return false;
	if (a.dd > b.dd) return true;
	return false;
}
bool operator>=(Date a, Date b) {
	return a == b || a > b;
}


Student* StringToStudent(std::wstring str) {
	//No, Student ID, First name, Last name, Gender, Date of Birth, Social ID
	Student* stu = new Student;
	wchar_t* temp = nullptr;
	int beg = str.find(L',', 0) + 1;
	int end = str.find(L',', beg);

	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	_LText();
	stu->ID = StringToInt(temp);
	stu->account.username = new char[end - beg + 1];
	stu->account.username[end - beg] = L'\0';
	LStrToStr(stu->account.username, end - beg, temp);
	delete[] temp;

	beg = end + 1;
	end = str.find(L',', beg);
	stu->firstname = new wchar_t[end - beg + 1];
	stu->firstname[end - beg] = L'\0';
	str.copy(stu->firstname, end - beg, beg);

	beg = end + 1;
	end = str.find(L',', beg);
	stu->lastname = new wchar_t[end - beg + 1];
	stu->lastname[end - beg] = L'\0';
	str.copy(stu->lastname, end - beg, beg);

	beg = end + 1;
	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	if (wcscmp(temp, L"Nam") == 0 || wcscmp(temp,L"Men"))stu->gender = 'M';
	else stu->gender = 'W';
	delete[] temp;

	beg = end + 1;
	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	stu->birth = StringToDate(temp);
	delete[] temp;


	beg = end + 1;
	end = str.length();
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	stu->SocialID = StringToInt(temp);
	delete[] temp;
	std::string pass;
	stu->birth.dd < 10 ? pass += "0" + std::to_string(stu->birth.dd) : pass += std::to_string(stu->birth.dd);
	stu->birth.mm < 10 ? pass += "0" + std::to_string(stu->birth.mm) : pass += std::to_string(stu->birth.mm);
	pass += std::to_string(stu->birth.yy);
	stu->account.password = new char[pass.length() + 1];
	for (int i = 0; i < pass.length(); i++) {
		stu->account.password[i] = pass[i];
	}
	stu->account.password[pass.length()] = '\0';
	return stu;
}
void AddStudent(_Student*& studentlist, Student* student) {
	if (studentlist == nullptr) { studentlist = new _Student{ student }; studentlist->pNext = studentlist, studentlist->pPrev = studentlist; return; }
	studentlist->pPrev = new _Student{ student,studentlist,studentlist->pPrev };
	studentlist->pPrev->pPrev->pNext = studentlist->pPrev;
}
_Student* FileInStudent(std::string filename) {
	_LText();
	std::wfstream fi(filename, std::wfstream::in);
	if (!fi) { return nullptr; }
	fi.imbue(std::locale(fi.getloc(), new std::codecvt_utf8<wchar_t>));
	fi.ignore(1i64, wchar_t(0xfeff));
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
	_LText();
	std::wfstream fo(fileout, std::wfstream::out);
	fo.imbue(std::locale(fo.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	_Student* temp = stu;
	fo << wchar_t(0xfeff);
	do
	{
		fo << stu->student->ID << L',' << stu->student->firstname << L',' << stu->student->lastname << L',' << stu->student->gender << L',' << stu->student->birth << L',' << stu->student->SocialID << L'\n';
		stu = stu->pNext;
	} while (stu != temp);
	fo.close();
	_SText();
}
void StuToBin(Student* stu, std::string fileout) {
	std::fstream fo(fileout, std::fstream::out | std::fstream::binary);
	int k = 0;
	k = strlen(stu->account.password) + 1;
	fo.write((char*)&k, sizeof(int));
	fo.write(stu->account.password, k);

	k = strlen(stu->account.username) + 1;
	fo.write((char*)&k, sizeof(int));
	fo.write(stu->account.username, k);

	k = wcslen(stu->firstname) + 1;
	fo.write((char*)&k, sizeof(int));
	fo.write((char*)&*stu->firstname, (sizeof(wchar_t) / sizeof(char)) * k);

	k = wcslen(stu->lastname) + 1;
	fo.write((char*)&k, sizeof(int));
	fo.write((char*)&*stu->lastname, (sizeof(wchar_t) / sizeof(char)) * k);

	fo.write(&stu->gender, 1);

	fo.write((char*)&stu->birth, sizeof(Date));

	if (stu->coursenow == nullptr) k = 0;
	else k = _msize(stu->coursenow) / sizeof(char*);
	fo.write((char*)&k, sizeof(int));
	for (int i = 0; i < k; i++) {
		int e = _msize(stu->coursenow[i]) / sizeof(char)+1;
		fo.write((char*)&e, sizeof(int));
		fo.write(stu->coursenow[i], e);
	}

	if (stu->allcourse == nullptr) k = 0;
	else k = _msize(stu->allcourse) / sizeof(char*);
	fo.write((char*)&k, sizeof(int));
	for (int i = 0; i < k; i++) {
		int e = _msize(stu->allcourse[i]) / sizeof(char) + 1;
		fo.write((char*)&e, sizeof(int));
		fo.write(stu->allcourse[i], e);
	}

	fo.write((char*)&stu->SocialID, sizeof(__int64));
	fo.write((char*)&stu->GPA, sizeof(float));

	fo.close();
}
Student* BinToStu(std::string filein) {
	std::fstream fi(filein, std::fstream::in | std::fstream::binary);
	if (!fi) { return nullptr; }
	Student* stu = new Student;
	int k = 0;
	fi.read((char*)&k, sizeof(int));
	stu->account.password = new char[k];
	fi.read(stu->account.password, k);

	fi.read((char*)&k, sizeof(int));
	stu->account.username = new char[k];
	fi.read(stu->account.username, k);

	stu->ID = StringToInt(stu->account.username);

	fi.read((char*)&k, sizeof(int));
	stu->firstname = new wchar_t[k];
	fi.read((char*)&*stu->firstname, (sizeof(wchar_t) / sizeof(char)) * k);

	fi.read((char*)&k, sizeof(int));
	stu->lastname = new wchar_t[k];
	fi.read((char*)&*stu->lastname, (sizeof(wchar_t) / sizeof(char)) * k);

	fi.read(&stu->gender, 1);

	fi.read((char*)&stu->birth, sizeof(Date));

	fi.read((char*)&k, sizeof(int));
	if (k > 0) stu->coursenow = new char* [k];
	else { stu->coursenow = nullptr; }
	for (int i = 0; i < k; i++) {
		int e = 0;
		fi.read((char*)&e, sizeof(int));
		stu->coursenow[i] = new char[e];
		fi.read(stu->coursenow[i], e);
	}

	fi.read((char*)&k, sizeof(int));
	if (k > 0) stu->allcourse = new char* [k];
	else {stu->coursenow = nullptr;}
	for (int i = 0; i < k; i++) {
		int e = 0;
		fi.read((char*)&e, sizeof(int));
		stu->allcourse[i] = new char[e];
		fi.read(stu->allcourse[i], e);
	}

	fi.read((char*)&stu->SocialID, sizeof(__int64));
	fi.read((char*)&stu->GPA, sizeof(float));

	fi.close();
	return stu;
}
void SaveNewStu(_Student* stu, char* direction) {
	if (stu == nullptr) return;
	char* direc = StrCat(direction, "\\Student\\");
	_Student* temp = stu;
	do {
		char* filename = NumToStr(stu->student->ID);
		char* fileout = AddTwoStr(direc, filename);
		StuToBin(stu->student, fileout);
		delete[] filename;
		delete[] fileout;
		stu = stu->pNext;
	} while (stu != temp);
	delete[] direc;
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
	std::wcout << a->ID<<'\t';
	std::wcout <<std::setw(25)<<std::left << a->firstname << std::setw(10);
	std::wcout << a->lastname<<'\t' << std::setw(11);
	if (a->gender == 'M' || a->gender=='N') std::wcout << "Men";
	else std::wcout << "Women";
	std::wcout <<std::left << a->birth << std::setw(15);
	std::wcout <<std::right<< a->SocialID << '\n';
	_SText();
}
void PrintStu(_Student* stu) {
	if (stu == nullptr) return;
	_Student* temp = stu;
	std::cout<<std::setw(5) << "ID" << std::setw(25) << "Fist Name" << std::setw(20) << "Last name" << std::setw(10) << "Gender" << std::setw(12) << "Birth" << std::setw(20) << "Social ID\n";
	do
	{
		PrintStu(stu->student);
		stu = stu->pNext;
	} while (stu != temp);
}

void PrintStu(Student** stu,int c) {
	if (stu == nullptr) return;
	system("cls");
	int n = _msize(stu) / sizeof(stu);
	int cur = c;
	char u;
	std::cout << std::setw(5) << "ID" << std::setw(25) << "Fist Name" << std::setw(20) << "Last name" << std::setw(10) << "Gender" << std::setw(12) << "Birth" << std::setw(20) << "Social ID";
	do {
		GotoXY(0, 1);
		for (int i = c-cur; i < c && i < n; i++) {
			PrintStu(stu[i]);
		}
		u = toupper(_getwch());
		if (u == 'A' || u == KEY_LEFT) {
			if (c != cur) {
				c -= cur;
				system("cls");
				std::cout << std::setw(5) << "ID" << std::setw(25) << "Fist Name" << std::setw(20) << "Last name" << std::setw(10) << "Gender" << std::setw(12) << "Birth" << std::setw(20) << "Social ID";
			}
		}
		if (u == 'D' || u == KEY_RIGHT) {
			if (c < n) {
				c += cur;
				system("cls");
				std::cout << std::setw(5) << "ID" << std::setw(25) << "Fist Name" << std::setw(20) << "Last name" << std::setw(10) << "Gender" << std::setw(12) << "Birth" << std::setw(20) << "Social ID";
			}
		}
	} while (u != KEY_ENTER);
}

Student* FindStudent(_Student* studentlist, unsigned __int64 ID) {
	if (studentlist == nullptr) return nullptr;
	_Student* temp = studentlist;
	while (studentlist->student->ID != ID && studentlist->pNext != temp)
	{
		studentlist = studentlist->pNext;
	}
	if (studentlist->student->ID != ID) { return nullptr; }
	return studentlist->student;
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
	while (pcur->student->ID != ID && pcur->pNext != temp)
	{
		pcur = pcur->pNext;
	}
	if (studentlist->student->ID != ID) return;
	if (pcur->pNext = pcur) studentlist = nullptr;
	pcur->pPrev->pNext = pcur->pNext;
	pcur->pNext->pPrev = pcur->pPrev;

	delete pcur;
}
void ConnectStudent(_Student*& a, _Student*& b) {
	if (a == nullptr) {
		a = b; b = nullptr; return;
	}

	a->pPrev->pNext = b;
	b->pPrev->pNext = a;
	_Student* temp = a->pPrev;
	a->pPrev = b->pPrev;
	b->pPrev = temp;
	b = nullptr;
}
int CountStudent(_Student* a) {
	if (a == nullptr) return 0;
	_Student* flag = a;
	int num = 0;
	do {
		num += 1;
		a = a->pNext;
	} while (a != flag);
	return num;
}

void AddClass(_Class*& cls, Classes sourse) {
	if (cls == nullptr) { cls = new _Class{ sourse }; cls->pNext = cls, cls->pPrev = cls; return; }
	cls->pPrev = new _Class{ sourse,cls,cls->pPrev };
	cls->pPrev->pPrev->pNext = cls->pPrev;
}


Classes MakeClass(_Student *&all,bool cls,int x, int y ) {
	if(cls) system("cls");
	Classes result;
	std::cout << "ClassName: ";
	std::string temp;
	std::cin >> temp;
	result.name = StrToChar(temp);
	char** chooselist = new char* [3];
	std::cout << "--------Add Student-------";
	chooselist[0] = new char[] {"From CSV"};
	chooselist[1] = new char[] {"TypeIn"};
	chooselist[2] = new char[] {"Add Later"};
	
	int take = Menu(chooselist, x, y);
	DealocatedArrString(chooselist);
	if (take == 0) {
		std::cout << "File in Student(.csv): ";
		std::cin >> temp;
		_Student* thisclass = FileInStudent(temp);
		result.numberofstudent = CountStudent(thisclass);
		thisclass = thisclass->pNext;
		if (result.numberofstudent != 0) {
			result.ID = new unsigned __int64[result.numberofstudent];
			for (int i = 0; i < result.numberofstudent; i++) {
				result.ID[i] = thisclass->student->ID;
				thisclass = thisclass->pNext;
			}
			for (int i = 0; i < result.numberofstudent; i++) {
				for (int j = i + 1; j < result.numberofstudent; j++) {
					if (result.ID[i] > result.ID[j]) {
						unsigned __int64 temp = result.ID[i];
						result.ID[i] = result.ID[j];
						result.ID[j] = temp;
					}
				}
			}
		}

		ConnectStudent(all, thisclass);
		return result;
	}
	if (take == 1) {
		_Student* thisclass = TypeInStudent();
		result.numberofstudent = CountStudent(thisclass);
		if (result.numberofstudent != 0) {
			result.ID = new unsigned __int64[result.numberofstudent];
			for (int i = 0; i < result.numberofstudent; i++) {
				result.ID[i] = thisclass->student->ID;
				thisclass = thisclass->pNext;
			}
		}
		ConnectStudent(all, thisclass);
		return result;
	}
	else {
		result.ID = nullptr;
		return result;
	}

}

_Student* TypeInStudent() {
	_Student* result = nullptr;
	char** chooselist = new char* [2];
	chooselist[0] = new char[] {"Add"};
	chooselist[1] = new char[] {"Done"};
	std::wstring temp;
	std::string temp1;
	int choose;
	do {
		Student* stu = new Student;
		std::cin.ignore(1000, '\n');
		std::cout << "ID: "; std::cin >> stu->ID;
		std::cin.ignore(1000, '\n');
		_LText();
		std::wcout << "Fistname: "; std::getline(std::wcin, temp); stu->firstname = StrToChar(temp);
		std::wcout << "Lastname: "; std::getline(std::wcin, temp); stu->lastname = StrToChar(temp);
		_SText();
		std::cout << "Gender: "; std::getline(std::cin, temp1);
		if (toupper(temp1[1])=='A' || toupper(temp[1]=='E'))
			stu->gender = 'M';
		do {
			std::cout << "Birth(dd/mm/yy): "; stu->birth = InputDate();
		} while (CheckDate(stu->birth)==false);
		std::cin.ignore(1000, '\n');
		std::cout << "Social ID: "; std::cin >> stu->SocialID;

		stu->account.username = NumToStr(stu->ID);
		temp1 = "";
		stu->birth.dd < 10 ? temp1 += "0" + std::to_string(stu->birth.dd) : temp1 += std::to_string(stu->birth.dd);
		stu->birth.mm < 10 ? temp1 += "0" + std::to_string(stu->birth.mm) : temp1 += std::to_string(stu->birth.mm);
		temp1 += std::to_string(stu->birth.yy);
		stu->account.password = new char[temp1.length() + 1];
		for (int i = 0; i < temp1.length(); i++) {
			stu->account.password[i] = temp1[i];
		}
		stu->account.password[temp1.length()] = '\0';
		AddStudent(result, stu);
		system("cls");
		std::cout << "------- Add Student -------";
		choose = Menu(chooselist, 5, 1);
	} while (choose==0);
	DealocatedArrString(chooselist);
	delete[] chooselist;//
	return result;
}

void SaveClass(Classes cl,const char* fileout) {
	std::fstream fo(fileout, std::fstream::out | std::fstream::binary);
	int k = strlen(cl.name) + 1;
	fo.write((char*)&k, sizeof(int));
	fo.write(cl.name, k);
	if (cl.ID == nullptr) k = 0;
	else k = cl.numberofstudent;
	fo.write((char*)&k, sizeof(int));
	for (int i = 0; i < k; i++) {
		fo.write((char*)&cl.ID[i], sizeof(unsigned __int64));
	}
	fo.close();
}

Classes* LoadClass(const char* filein) {
	Classes* result = new Classes;
	std::fstream fi(filein, std::fstream::in | std::fstream::binary);
	int k;
	fi.read((char*)&k, sizeof(int));
	result->name = new char[k];
	fi.read(result->name, k);
	fi.read((char*)&result->numberofstudent, sizeof(int));
	result->ID = new unsigned __int64[result->numberofstudent];
	for (int i = 0; i < result->numberofstudent; i++) {
		fi.read((char*)&result->ID[i], sizeof(__int64));
	}
	return result;
}

void SaveClass(_Class* cls, char* direction) {
	if (cls == nullptr) return;
	char* direc = StrCat(direction, "\\Class\\");
	_Class* temp = cls;
	do {
		char* direction = StrCat(direc, cls->classes.name);
		SaveClass(cls->classes, direction);
		delete[] direction;
		cls = cls->pNext;
	} while (cls != temp);
}

void PrintClass(Classes a) {
	_SText();
	std::cout << a.name<<'\n';
	int n = _msize(a.ID) / sizeof(__int64);
	if (a.ID != nullptr) {
		for (int i = 0; i < n; i++) {
			std::cout << a.ID[i] << '\n';
		}
	}
}


SchoolYear* AddSchoolYear(int year) {
	wchar_t* data = new wchar_t[] {L"Data"};
	_wmkdir(data);
	delete[]data;
	data = new wchar_t[] {L"Data\\Grade"};
	_wmkdir(data);
	delete[] data;
	SchoolYear* a = new SchoolYear;
	a->year = year;
	wchar_t* yy = NumToLStr(a->year);
	wchar_t* file = new wchar_t[]{ L"Data\\Grade\\K" };
	StrCat(file, wcslen(yy), yy);
	_wmkdir(file);
	wchar_t* temp = StrCat(file, L"\\Student");
	_wmkdir(temp);
	delete[] temp;
	temp = StrCat(file, L"\\Class");
	_wmkdir(temp);
	delete[] temp;
	a->classes = nullptr;
	a->student = nullptr;
	int chose;
	char** choselist = new char* [2];
	choselist[0] = new char[] {"AddClass"};
	choselist[1] = new char[] {"Done"};
	system("cls");
	chose = Menu(choselist, 5, 0);
	while (chose==0)
	{
		Classes tt = MakeClass(a->student);
		AddClass(a->classes,tt);
		system("cls");
		std::cout << "------- Add Class -------";
		chose = Menu(choselist, 5, 1);
	}
	DealocatedArrString(choselist);
	delete[]yy, file;
	return a;
}
void SaveSchoolYear(SchoolYear*sch) {
	if (sch == nullptr) return;
	char* local = new char[] {"Data\\Grade\\K"};
	char* year = NumToStr(sch->year);
	char* direction = StrCat(local, year);
	SaveNewStu(sch->student, direction);
	SaveClass(sch->classes, direction);
	delete[]local, year, direction;
}

void MakeCurentTime(int year) {
	wchar_t*curent = new wchar_t[] {L"Data"};
	_wmkdir(curent);
	delete[] curent;
	curent = new wchar_t[] {L"Data\\SchoolYear"};
	_wmkdir(curent);
	wchar_t* temp = StrCat(curent, L"\\");
	delete[] curent;
	StrCat(temp, std::to_string(year).length(), std::to_wstring(year));
	if (_wmkdir(temp) == -1) { std::cout << "--Warning! override time--\n"; };
	StrCat(temp, 2, L"\\");
	for (int i = 0; i < 3; i++) {
		wchar_t* semester = StrCat(temp, L"Semester" + std::to_wstring(i + 1));
		_wmkdir(semester);
		delete[] semester;
	}
	wchar_t* SemesterTime = StrCat(temp, L"time");
	std::fstream fo(SemesterTime,std::fstream::out|std::fstream::binary);
	std::cin.clear();
	Date start[3], end[3];
	char** menu = new char* [2];
	menu[0] = new char[] {"Confirm"};
	menu[1] = new char[] {"Again"};
	do
	{
		for (int i = 0; i < 3; i++) {
			std::cout << "Date start semester " << i + 1 << ": ";
			while (true)
			{
				start[i] = InputDate();
				if (CheckDate(start[i]) == false || (i == 0 ? false : !(start[i] >= start[i - 1]))) {
					std::cout << "     Date not invalid! ";
				}
				else break;
			}
			std::cout << "Date end semester " << i + 1 << ": ";
			while (true)
			{
				end[i] = InputDate();
				if (CheckDate(end[i]) == false || end[i] < start[i] || (i == 0 ? false : !(end[i] >= end[i - 1]))) {
					std::cout << "     Date not invalid! ";
				}
				else break;
			}
		}
		system("cls");
		std::cout << "--------------------------------------------\n";
		for (int i = 0; i < 3; i++) {
			std::cout << "Semester " << i + 1 << "\t start: " << start[i] << "\tend:" << end[i] << '\n';
		}
	} while (Menu(menu, 6, 5) != 0);
	for (int i = 0; i < 3; i++) {
		fo.write((char*)&start[i], sizeof(Date));
		fo.write((char*)&end[i], sizeof(Date));
	}
	DealocatedArrString(menu);
	delete[] temp, SemesterTime;//
	fo.close();
}

int CountFile(Filelist* a) {
	if (a == nullptr || a->filename == "..") return 0;
	Filelist* flag = a;
	int num = 0;
	do {
		num += 1;
		a = a->pNext;
	} while (a != flag);
	return num;
}

std::string ViewSemesterTime() {
	Filelist* a = TakeFileInFolder("Data\\SchoolYear");
	int size = CountFile(a);
	char** list = new char* [size];
	for (int i = 0; i < size; i++) {
		list[i] = StrToChar(a->filename);
		a = a->pNext;
	}
	std::string current = "Data\\SchoolYear\\" + ToString(list[Menu(list, 10, 10)]);
	wchar_t** k = new wchar_t* [3];
	for (int i = 0; i < 3; i++) {
		k[i] = new wchar_t[10] {L"Semester"};
		k[i][8] = i + 1 + L'0';
		k[i][9] = L'\0';
	}
	current += "\\Semester" + std::to_string(Menu(k, 20, 20) + 1) + "\\";
	delete[] list, k;
	std::fstream fo("beggin", std::fstream::out);
	fo << current;
	fo.close();
	return current;
}



void AddInListFile(Filelist*& direc, std::string add) {
	if (direc == nullptr) { direc = new Filelist{ add }; direc->pNext = direc, direc->pPrev = direc; return; }
	direc->pPrev = new Filelist{ add,direc,direc->pPrev };
	direc->pPrev->pPrev->pNext = direc->pPrev;
}
//it will have bug here
void SaveScore(Score* score, std::string filename) {
	std::fstream fo(filename, std::fstream::out | std::fstream::binary);
	if (score == nullptr) { fo.close(); return; }
	int n = _msize(score) / sizeof(score);
	for (int i = 0; i < n; i++) {
		fo.write((char*)&score[i], sizeof(Score));
	}
	fo.close();
}

void LoadScore(Score*score, std::string filename) {
	if (score == nullptr) return;
	std::fstream fi(filename, std::fstream::in | std::fstream::binary);
	int n = _msize(score) / sizeof(Score);
	for(int i=0;i<n;i++){
		fi.read((char*)&score[i], sizeof(Score));
	}
	fi.close();
}

void CourseToBin(Course* course, std::string filename,std::string current) {
	std::fstream fo(current+"\\"+filename, std::fstream::out | std::fstream::binary);
	int k;

	fo.write((char*)&course->numberofstudent, sizeof(unsigned short));
	fo.write((char*)&course->maxstudent, sizeof(unsigned short));
	fo.write((char*)&course->performed[0].day, sizeof(unsigned short));
	fo.write((char*)&course->performed[0].session, sizeof(unsigned short));
	fo.write((char*)&course->performed[1].day, sizeof(unsigned short));
	fo.write((char*)&course->performed[1].session, sizeof(unsigned short));
	fo.write((char*)&course->credit, sizeof(unsigned short));

	k = strlen(course->ID) + 1;
	fo.write((char*)&k, sizeof(int));
	fo.write(course->ID, k);

	k = wcslen(course->name) + 1;
	fo.write((char*)&k, sizeof(int));
	fo.write((char*)&*course->name, (sizeof(wchar_t) / sizeof(char) * k));

	k = wcslen(course->teacher) + 1;
	fo.write((char*)&k, sizeof(int));
	fo.write((char*)&*course->teacher, (sizeof(wchar_t) / sizeof(char) * k));

	for (int i = 0; i < course->numberofstudent; i++) {
		fo.write((char*)&course->stuID[i], sizeof(unsigned __int64));
	}
	fo.close();
}

void CourseToBin(_Course* course, std::string current) {
	if (course == nullptr) return;
	_Course* temp = course;
	do {
		CourseToBin(course->course, ToString(course->course->ID), current);
		course = course->pNext;
	} while (temp != course);
}

Course* BinToCourse(std::string filename) {
	std::fstream fi(filename, std::fstream::in | std::fstream::binary);
	if (!fi) return nullptr;
	int k;
	Course* course = new Course;

	fi.read((char*)&course->numberofstudent, sizeof(unsigned short));
	fi.read((char*)&course->maxstudent, sizeof(unsigned short));
	fi.read((char*)&course->performed[0].day, sizeof(unsigned short));
	fi.read((char*)&course->performed[0].session, sizeof(unsigned short));
	fi.read((char*)&course->performed[1].day, sizeof(unsigned short));
	fi.read((char*)&course->performed[1].session, sizeof(unsigned short));
	fi.read((char*)&course->credit, sizeof(unsigned short));

	fi.read((char*)&k, sizeof(int));
	course->ID = new char[k];
	fi.read(course->ID, k);

	fi.read((char*)&k, sizeof(int));
	course->name = new wchar_t[k];
	fi.read((char*)&*course->name, (sizeof(wchar_t) / sizeof(char) * k));

	fi.read((char*)&k, sizeof(int));
	course->teacher = new wchar_t[k];
	fi.read((char*)&*course->teacher, (sizeof(wchar_t) / sizeof(char) * k));

	for (int i = 0; i < course->numberofstudent; i++) {
		fi.read((char*)&course->stuID[i], sizeof(unsigned __int64));
	}
	course->score = new Score[course->numberofstudent];
	LoadScore(course->score, filename + "Scores");
	fi.close();
	return course;
}
std::string TakeCurrent() {
	Filelist* Plan = TakeFileInFolder("Data\\SchoolYear");
	int n = CountFile(Plan);
	std::string year = "";
	char semester;
	Date temp = GetTime();
	Date start, end;
	std::fstream fi;
	for (int i = 0; i < n; i++) {
		fi.open("Data\\SchoolYear\\" + Plan->filename + "\\time", std::fstream::in | std::fstream::binary);
		for (int k = 0; k < 3; k++)
		{
			fi.read((char*)&start, sizeof(Date));
			fi.read((char*)&end, sizeof(Date));
			if (start <= temp && end >= temp) { year = Plan->filename; semester = k + 1 + '0'; }
		}
		Plan = Plan->pNext;
	}

	//deallocated plan here;
	if (year == "") return "";
	return "Data\\SchoolYear\\" + year + "\\Semester" + semester;
}