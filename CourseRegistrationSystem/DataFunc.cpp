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
	if (dt.dd < 10) os << "0" << dt.dd << '/';
	else os << dt.dd << '/';
	if (dt.mm < 10) os << "0" << dt.mm << '/';
	else os << dt.mm << '/';
	os << dt.yy;
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
	std::string pass = std::to_string(stu.birth.dd) + std::to_string(stu.birth.mm) + std::to_string(stu.birth.yy);
	stu.account.password = new char[pass.length()+1];
	for (int i = 0; i < pass.length(); i++) {
		stu.account.password[i] = pass[i];
	}
	stu.account.password[pass.length()] = '\0';
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
void SaveNewStu(_Student* stu, char* direction) {
	if (stu == nullptr) return;
	char* direc = StrCat(direction, "\\Student\\");
	_Student* temp = stu;
	do {
		char* filename = NumToStr(stu->student.ID);
		char* fileout = AddTwoStr(direc, filename);
		StuToBin(&stu->student, fileout);
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
void SaveSchoolYear(SchoolYear*sch) {
	if (sch == nullptr) return;
	char* local = new char[] {"Data\\K"};
	char* year = NumToStr(sch->year);
	char* direction = StrCat(local, year);
	SaveNewStu(sch->student, direction);
	SaveClass(sch->classes, direction);
	delete[]local, year, direction;
}

void MakeCurentTime(__int64 year) {
	wchar_t* curent = new wchar_t[] {L"Data\\SchoolYear"};
	_wmkdir(curent);
	wchar_t* temp = StrCat(curent, L"\\");
	StrCat(temp, std::to_string(year).length(), std::to_wstring(year));
	_wmkdir(temp);
	StrCat(temp, 2, L"\\");
	for (int i = 0; i < 3; i++) {
		wchar_t* semester = StrCat(temp, L"Semester" + std::to_wstring(i + 1));
		_wmkdir(semester);
		delete[] semester;
	}
	wchar_t* SemesterTime = StrCat(temp, L"time");
	std::fstream fo(SemesterTime,std::fstream::out|std::fstream::binary);
	std::cin.ignore(1i64, '\n');
	for (int i = 0; i < 3; i++) {
		Date a;
		std::cout << "Date start semester " << i + 1 << ": ";
		std::string k;;
		std::getline(std::cin, k);
		a = StringToDate(k);
		fo.write((char*)&a, sizeof(Date));
		std::cout << "Date end semester " << i + 1 << ": ";
		std::getline(std::cin, k);
		a = StringToDate(k);
		fo.write((char*)&a, sizeof(Date));
	}
	fo.close();
}

int CountFile(Filelist* a) {
	if (a == nullptr) return 0;
	Filelist* flag = a;
	int num = 0;
	do {
		num += 1;
		a = a->pNext;
	} while (a != flag);
	return num;
}

std::wstring ChooseCurrentTime() {
	Filelist* a = TakeFileInFolder("Data\\SchoolYear");
	int size = CountFile(a);
	wchar_t** list = new wchar_t* [size];
	for (int i = 0; i < size; i++) {
		list[i] = StrToChar(a->filename);
		a = a->pNext;
	}
	std::wstring current = L"Data\\SchoolYear\\"+ToWstring(list[Menu(list, 10, 10)]);
	wchar_t** k = new wchar_t* [3];
	for (int i = 0; i < 3; i++) {
		k[i] = new wchar_t[10] {L"Semester"};
		k[i][8] = i + 1 + L'0';
		k[i][9] = L'\0';
	}
	current += L"\\Semester" + std::to_wstring(Menu(k, 20, 20) + 1) + L"\\";
	delete[] list, k;
	std::wfstream fo("beggin", std::wfstream::out);
	fo << current;
	fo.close();
	return current;
}



void AddInListFile(Filelist*& direc, std::wstring add) {
	if (direc == nullptr) { direc = new Filelist{ add }; direc->pNext = direc, direc->pPrev = direc; return; }
	direc->pPrev = new Filelist{ add,direc,direc->pPrev };
	direc->pPrev->pPrev->pNext = direc->pPrev;
}

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

void CourseToBIn(Course* course, std::string filename,std::wstring current) {
	std::fstream fo(ToString(current)+filename, std::fstream::out | std::fstream::binary);
	int k;

	k = strlen(course->ID) + 1;
	fo.write((char*)&k, sizeof(int));
	fo.write(course->ID, k);

	k = wcslen(course->name) + 1;
	fo.write((char*)&k, sizeof(int));
	fo.write((char*)&course->name, 2 * k);

	k = wcslen(course->teacher) + 1;
	fo.write((char*)&k, sizeof(int));
	fo.write((char*)&course->teacher, 2 * k);

	fo.write((char*)&course->performed[0].day, sizeof(short));
	fo.write((char*)&course->performed[0].session, sizeof(short));
	fo.write((char*)&course->performed[1].day, sizeof(short));
	fo.write((char*)&course->performed[1].session, sizeof(short));

	fo.write((char*)&course->credit, sizeof(short));
	fo.write((char*)&course->maxstudent, sizeof(short));
	fo.write((char*)&course->numberofstudent, sizeof(short));
	
	for (int i = 0; i < course->numberofstudent; i++) {
		fo.write((char*)&course->ID[i], sizeof(__int64));
	}
	SaveScore(course->score, ToString(current) + filename + "Score");
	fo.close();
}

Course BinToCourse(std::string filename) {
	Course course;
	std::fstream fi(filename, std::fstream::in | std::fstream::binary);
	int k;

	fi.read((char*)&k, sizeof(int));
	course.ID = new char[k];
	fi.read(course.ID, k);

	fi.read((char*)&k, sizeof(int));
	course.name = new wchar_t[k];
	fi.read((char*)&course.name, 2 * k);

	fi.read((char*)&k, sizeof(int));
	course.teacher = new wchar_t[k];
	fi.read((char*)&course.teacher, 2 * k);

	fi.read((char*)&course.performed[0].day, sizeof(short));
	fi.read((char*)&course.performed[0].session, sizeof(short));
	fi.read((char*)&course.performed[1].day, sizeof(short));
	fi.read((char*)&course.performed[1].session, sizeof(short));

	fi.read((char*)&course.credit, sizeof(short));
	fi.read((char*)&course.maxstudent, sizeof(short));
	fi.read((char*)&course.numberofstudent, sizeof(short));

	for (int i = 0; i < course.numberofstudent; i++) {
		fi.read((char*)&course.ID[i], sizeof(__int64));
	}
	course.score = new Score[course.numberofstudent];
	LoadScore(course.score, filename + "Score");
	return course;
}