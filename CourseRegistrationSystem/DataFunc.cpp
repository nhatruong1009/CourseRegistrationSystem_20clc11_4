#include"Data.h"
#include"CommonFunc.h"
#include <sys/stat.h>
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
	_LText();
	std::wfstream fo(fileout, std::wfstream::out);
	fo.imbue(std::locale(fo.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	_Student* temp = stu;
	fo << wchar_t(0xfeff);
	do
	{
		fo << stu->student.ID << L',' << stu->student.firstname << L',' << stu->student.lastname << L',' << stu->student.gender << L',' << stu->student.birth << L',' << stu->student.SocialID << L'\n';
		stu = stu->pNext;
	} while (stu != temp);
	fo.close();
	_SText();
}
void StuToBin(Student* stu, std::string fileout) {
	std::fstream fo(fileout, std::fstream::out | std::fstream::binary);
	int k = 0;
	k = _msize(stu->account.password) / sizeof(char) + 1;
	fo.write((char*)&k, sizeof(int));
	fo.write(stu->account.password, k);

	k = _msize(stu->account.username) / sizeof(char) + 1;
	fo.write((char*)&k, sizeof(int));
	fo.write(stu->account.username, k);

	k = _msize(stu->firstname) / sizeof(char) + 1;
	fo.write((char*)&k, sizeof(int));
	fo.write((char*)&*stu->firstname, 2 * k);

	k = _msize(stu->lastname) / sizeof(char) + 1;
	fo.write((char*)&k, sizeof(int));
	fo.write((char*)&*stu->lastname, 2 * k);

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
Student BinToStu(std::string filein) {
	Student stu;
	std::fstream fi(filein, std::fstream::in | std::fstream::binary);
	if (!fi) { return stu; }
	int k = 0;
	fi.read((char*)&k, sizeof(int));
	stu.account.password = new char[k];
	fi.read(stu.account.password, k);

	fi.read((char*)&k, sizeof(int));
	stu.account.username = new char[k];
	fi.read(stu.account.username, k);

	stu.ID = StringToInt(stu.account.username);

	fi.read((char*)&k, sizeof(int));
	stu.firstname = new wchar_t[k];
	fi.read((char*)&*stu.firstname, 2 * k);

	fi.read((char*)&k, sizeof(int));
	stu.lastname = new wchar_t[k];
	fi.read((char*)&*stu.lastname, 2 * k);

	fi.read(&stu.gender, 1);

	fi.read((char*)&stu.birth, sizeof(Date));

	fi.read((char*)&k, sizeof(int));
	if (k > 0) stu.coursenow = new char* [k];
	for (int i = 0; i < k; i++) {
		int e = 0;
		fi.read((char*)&e, sizeof(int));
		stu.coursenow[i] = new char[e];
		fi.read(stu.coursenow[i], e);
	}

	fi.read((char*)&k, sizeof(int));
	if (k > 0) stu.allcourse = new char* [k];
	for (int i = 0; i < k; i++) {
		int e = 0;
		fi.read((char*)&e, sizeof(int));
		stu.allcourse[i] = new char[e];
		fi.read(stu.allcourse[i], e);
	}

	fi.read((char*)&stu.SocialID, sizeof(__int64));
	fi.read((char*)&stu.GPA, sizeof(float));

	fi.close();
	return stu;
}
void SaveNewStu(_Student* stu, char* direction, const char* savefile) {
	if (stu == nullptr) return;
	char* direc = StrCat(direction, "\\Student\\");
	std::fstream fii(savefile, std::fstream::app);
	_Student* temp = stu;
	do {
		char* filename = NumToStr(stu->student.ID);
		char* fileout = AddTwoStr(direc, filename);
		StuToBin(&stu->student, fileout);
		fii << filename << " " << fileout << '\n';
		delete[] filename;
		delete[] fileout;
		stu = stu->pNext;
	} while (stu != temp);
	delete[] direc;
	fii.close();
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
Classes MakeClass(_Student *&all) {
	Classes result;
	std::cout << "ClassName: ";
	std::string temp;
	std::cin >> temp;
	result.name = StrToChar(temp);
	std::cout << "File in Student(.csv): ";
	std::cin >> temp;
	_Student* thisclass = FileInStudent(temp);
	int numberofstu = CountStudent(thisclass);
	if (numberofstu != 0) {
		result.ID = new unsigned __int64[numberofstu];
		for (int i = 0; i < numberofstu; i++) {
			result.ID[i] = thisclass->student.ID;
			thisclass = thisclass->pNext;
		}
	}
	ConnectStudent(all, thisclass);
	return result;
}

void SaveClass(Classes cl, char* fileout) {
	std::fstream fo(fileout, std::fstream::out | std::fstream::binary);
	int k;
	if (cl.ID == nullptr) k = 0;
	else k = _msize(cl.ID) / sizeof(__int64*);
	fo.write((char*)&k, sizeof(int));
	for (int i = 0; i < k; i++) {
		fo.write((char*)&cl.ID[i], sizeof(__int64));
	}
	fo.close();
}

void SaveClass(_Class* cls, char* direction, const char* savefile) {
	if (cls == nullptr) return;
	char* direc = StrCat(direction, "\\Class\\");
	std::fstream fii(savefile, std::fstream::app | std::fstream::binary);
	_Class* temp = cls;
	int n;
	do {
		char* direction = StrCat(direc, cls->classes.name);
		SaveClass(cls->classes, direction);
		n = strlen(cls->classes.name);
		fii << cls->classes.name << " " << direc << '\n';
		delete[] direction;
		cls = cls->pNext;
	} while (cls != temp);
	fii.close();
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
SchoolYear* AddSchoolYear() {
	wchar_t* data = new wchar_t[] {L"Data"};
	_wmkdir(data);
	delete[] data;
	SchoolYear* a = new SchoolYear;
	tm now = GetTime();
	a->year = now.tm_year;
	wchar_t* yy = NumToLStr(a->year);
	wchar_t* file = new wchar_t[]{ L"Data\\K" };
	StrCat(file, wcslen(yy), yy);
	if (_wmkdir(file)==-1) {
		std::cout << "School year had made!";
		delete a;
		delete[]yy, file;
		return nullptr;
	}
	else {
		wchar_t* temp = StrCat(file, L"\\Student");
		_wmkdir(temp);
		delete[] temp;
		temp = StrCat(file, L"\\Class");
		_wmkdir(temp);
		delete[] temp;
		temp = StrCat(file, L"\\Course");
		_wmkdir(temp);
		wchar_t*temp2 = StrCat(temp, L"\\Score");
		_wmkdir(temp2);
		delete[] temp, temp2;

		a->classes = nullptr;
		a->student = nullptr;
		int chose;
		std::cout << "1:AddClass\n";
		std::cin >> chose;
		while (chose==1)
		{
			Classes tt = MakeClass(a->student);
			AddClass(a->classes,tt);
			std::cin >> chose;
		}
		delete[]yy, file;
		return a;
	}
}
void SaveSchoolYear(SchoolYear*sch,const char*savefile) {
	if (sch == nullptr) return;
	char* local = new char[] {"Data\\K"};
	char* year = NumToStr(sch->year);
	char* direction = StrCat(local, year);
	SaveNewStu(sch->student, direction, "student.txt");
	SaveClass(sch->classes, direction, "class.txt");
	std::fstream fo(savefile, std::fstream::app);
	fo << sch->year << " " << direction;
	delete[]local, year, direction;
}

