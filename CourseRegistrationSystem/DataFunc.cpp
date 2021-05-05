#include"Data.h"
#include"Sup.h"
#include"Interface.h"
#include"Staff.h"
#include"Student.h"
//****************Another SupFunc******
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

//****************DATE*****************
Date GetTime()
{
	__time32_t now = time(0);
	tm t;
	_localtime32_s(&t, &now);
	t.tm_year += 1900;
	t.tm_mon += 1;
	Date temp;
	temp.dd = t.tm_mday;
	temp.mm = t.tm_mon;
	temp.yy = t.tm_year;
	return temp;
}
Date InputDate() {
	char temp;
	std::string result = "";
	while (true)
	{
		temp = _getwch();
		if (temp == KEY_ESC) { return Date{ 00,00,0000 }; }
		if (result.size() == 10 && temp == KEY_ENTER) {
			std::cout << "\n";
			break;
		}
		if (temp <= '9' && temp >= '0' && result.size() < 10) {
			if (result.size() == 2 || result.size() == 5) {
				std::cout << "/" << temp;
				result.push_back(' ');
				result.push_back(temp);
			}
			else {
				std::cout << temp;
				result.push_back(temp);
			}
		}
		if (temp == KEY_BACKSPACE && result.size() > 0) {
			if (result.size() == 3 || result.size() == 6)
			{
				result.pop_back();
				result.pop_back();
				std::cout << temp << temp << "  " << temp << temp;
			}
			else {
				result.pop_back();
				std::cout << temp << ' ' << temp;
			}
		}
		if ((temp == '/' || temp == ' ' || temp == '-') && (result.size() == 1 || result.size() == 4)) {
			char a = result[result.size() - 1];
			result.pop_back();
			result.push_back('0');
			result.push_back(a);
			result.push_back('/');
			std::cout << char(8) << '0' << a << '/';
		}
	}
	return StringToDate(result);
}
Date TakeDateEnd(std::string current) {
	int sem = current.find('\\', 0);
	sem = current.find('\\', sem + 1);
	int temp = current.find('\\', sem + 1);
	char* year = new char[temp - sem];
	current.copy(year, temp - sem, sem + 1);
	year[temp - sem - 1] = '\0';
	sem = current[current.size() - 1] - '0';

	std::fstream fi("Data\\SchoolYear\\" + ToString(year) + "\\time", std::fstream::in | std::fstream::binary);
	Date check;
	for (int i = 0; i < sem; i++) {
		fi.read((char*)&check, sizeof(Date));
		fi.read((char*)&check, sizeof(Date));
	}
	delete[] year;
	return check;
}
Date TakeDateStart(std::string current) {
	int sem = current.find('\\', 0);
	sem = current.find('\\', sem + 1);
	int temp = current.find('\\', sem + 1);
	char* year = new char[temp - sem];
	current.copy(year, temp - sem, sem + 1);
	year[temp - sem - 1] = '\0';
	sem = current[current.size() - 1] - '0';

	std::fstream fi("Data\\SchoolYear\\" + ToString(year) + "\\time", std::fstream::in | std::fstream::binary);
	Date check;
	fi.read((char*)&check, sizeof(Date));
	for (int i = 1; i < sem; i++) {
		fi.read((char*)&check, sizeof(Date));
		fi.read((char*)&check, sizeof(Date));
	}
	delete[] year;
	return check;
}
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
bool LeapYear(int y)
{
	if (y % 400 == 0)
		return 1;
	else if (y % 4 == 0 && y % 25 != 0)
		return 1;
	return 0;
}
bool CheckDate(Date dat)
{
	int d = dat.dd;
	int m = dat.mm;
	int y = dat.yy;
	if (d < 1 || m < 1 || y < 0 || m > 12)
		return 0;
	if (LeapYear(y))
	{
		if (m == 2 && d > 29)
			return 0;
	}
	else
	{
		if (m == 2 && d > 28)
			return 0;
	}
	if (d > 31) return 0;
	if (d > 30)
		if (m == 4 || m == 6 || m == 9 || m == 11)
			return 0;
	return 1;
}
//**************Score******************
Score* LoadScore(std::string filename) {
	std::fstream fi(filename, std::fstream::in | std::fstream::binary);
	if (!fi) return nullptr;
	unsigned short numberofstu;
	fi.read((char*)&numberofstu, sizeof(unsigned short));
	Score* sco = new Score[numberofstu];
	for (int i = 0; i < numberofstu; i++) {
		fi.read((char*)sco[i].ID, sizeof(unsigned __int64));
		fi.read((char*)&sco[i].totals, sizeof(float) * 4);
	}
	return sco;
}

void SaveScore(Course* cou, std::string filename) {
	if (cou == nullptr) return;
	std::fstream fo(filename, std::fstream::out | std::fstream::binary);
	fo.write((char*)&cou->numberofstudent, sizeof(unsigned short));
	float temp[4] = { 0,0,0,0 };
	for (int i = 0; i < cou->numberofstudent; i++) {
		fo.write((char*)&cou->stuID[i], sizeof(unsigned __int64));
		fo.write((char*)temp, sizeof(float) * 4);
	}
	fo.close();
}
void SaveScore(Course* cou, Score* score, std::string filename) {
	if (cou == nullptr) return;
	std::fstream fo(filename, std::fstream::out | std::fstream::binary);
	fo.write((char*)&cou->numberofstudent, sizeof(unsigned short));
	for (int i = 0; i < cou->numberofstudent; i++) {
		fo.write((char*)cou->stuID[i], sizeof(unsigned __int64));
		fo.write((char*)&score->totals, sizeof(float) * 4);
	}
	fo.close();
}
Score GetStuScore(std::string path, Student* stu)
{
	std::ifstream fin(path, std::ios::binary);
	if (!fin)
		return Score{};
	Score a;
	short n;
	fin.read((char*)&n, sizeof(n));
	unsigned __int64 temp;
	fin.read((char*)&temp, 8);
	while (temp != stu->ID)
	{
		fin.seekg(16, fin.cur);
		fin.read((char*)&temp, 8);
		if (fin.eof())
		{
			std::cout << "Not found " << stu->ID;
			fin.close();
			return Score{};
		}
	}
	a.ID = temp;
	fin.read((char*)&a.totals, 4);
	fin.read((char*)&a.finals, 4);
	fin.read((char*)&a.mids, 4);
	fin.read((char*)&a.others, 4);
	fin.close();
	return a;
}
Score GetScore(Student* a, Course* course)
{
	std::string courseID = ToString(course->ID);
	int n = courseID.size();
	if (n < 5)
	{
		return Score{};
	}
	std::string semester = "Semester";
	semester += courseID[n];
	std::string year = "";
	year = year + courseID[n - 4] + courseID[n - 3] + courseID[n - 2] + courseID[n - 1];
	for (int i = 0; i < 5; i++)
		courseID.pop_back();
	Score result = GetStuScore("Data\\SchoolYear\\" + year + "\\" + semester + "\\" + courseID + "Score", a);
	result.ID = a->ID;
	return result;
}

//**************Course*****************
Course* MakeCourse() {
	Course* result = new Course;

	std::string stemp;
	std::cout << "Course ID: ";
	std::getline(std::cin, stemp);
	int size = stemp.length();
	result->ID = new char[size + 1];
	result->ID[size] = '\0';
	stemp.copy(result->ID, size);

	_LText();
	std::wcout << "Course name: ";
	std::wstring temp;
	std::getline(std::wcin, temp);
	size = temp.length();
	result->name = new wchar_t[size + 1];
	result->name[size] = L'\0';
	temp.copy(result->name, size);

	std::wcout << "Teacher name: ";
	std::getline(std::wcin, temp);
	size = temp.length();
	result->teacher = new wchar_t[size + 1];
	result->teacher[size] = L'\0';
	temp.copy(result->teacher, size);
	_SText();

	std::cout << "Number of credits: ";
	std::cin >> result->credit;
	std::cin.ignore(1000, '\n');

	std::cout << "Schedule \n";// hmm not workking
	pickSchedule(result, 10, 4);

	return result;
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

	course->stuID = new unsigned __int64[course->numberofstudent];
	for (int i = 0; i < course->numberofstudent; i++) {
		fi.read((char*)&course->stuID[i], sizeof(unsigned __int64));
	}
	fi.close();
	return course;
}
Course* searchCourseFile(std::string search) {
	char year[5];
	year[4] = '\0';
	int size = search.length();
	int n = size - 5;
	for (int i = 0; i < 4; i++) {
		year[i] = search[n + i];
	}
	char* local = new char[] {"Data\\SchoolYear"};
	char* temp = StrCat(year, "\\Semester" + search[size - 1]);
	char* temp1 = StrCat(temp, "\\");
	delete[]temp;
	StrCat(temp1, size - 5, search);
	char* direction = StrCat(local, temp1);
	Course* cou = BinToCourse(direction);
	if (cou == nullptr) std::cout << "Unable to find " << search << "\n";
	delete[]temp1, direction, local;
	return cou;
}

void AddCourse(_Course*& courselist, Course* course) {
	if (courselist == nullptr) { courselist = new _Course{ course }; courselist->pNext = courselist, courselist->pPrev = courselist; return; }
	courselist->pPrev = new _Course{ course,courselist,courselist->pPrev };
	courselist->pPrev->pPrev->pNext = courselist->pPrev;
}
void MakeCourse(std::string current) {
	system("cls");
	char** menu = new char* [2];
	_Course* cou = nullptr;
	menu[0] = new char[] {"Add Course"};
	menu[1] = new char[] {"Done"};
	int check = Menu(menu, 5, 2);
	while (check == 0)
	{
		system("cls");
		AddCourse(cou, MakeCourse());
		system("cls");
		check = Menu(menu, 5, 2);
	}
	std::cout << "Saving.... ";
	CourseToBin(cou, current);
	std::cout << "\n> done <";
	_getwch();
	DealocatedArrString(menu);
	delete_Course(cou);
}
void CourseToBin(_Course* course, std::string current) {
	if (course == nullptr) return;
	_Course* temp = course;
	do {
		CourseToBin(course->course, ToString(course->course->ID), current);
		course = course->pNext;
	} while (temp != course);
}
void CourseToBin(Course* course, std::string filename, std::string current) {
	std::fstream fo(current + "\\" + filename, std::fstream::out | std::fstream::binary);
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
void registerCourse(Course** newReg, std::string sem, unsigned __int64 stuID) {
	if (newReg == nullptr) return;
	int n = _msize(newReg) / sizeof(newReg);
	for (int i = 0; i < n; i++) {
		newReg[i]->numberofstudent += 1;
		std::fstream filecou(sem + "\\" + newReg[i]->ID, std::fstream::in | std::fstream::out | std::fstream::binary);
		filecou.seekp(0, std::fstream::beg);
		filecou.write((char*)&newReg[i]->numberofstudent, sizeof(unsigned short));
		filecou.seekp(0, std::fstream::end);
		filecou.write((char*)&stuID, sizeof(unsigned __int64));
		filecou.close();
		char* accountID = StrToChar(NumToStr(stuID));
		SaveCourseRegHis(accountID, *newReg[i]);
		delete[]accountID;
	}
}
void cancelCourse(Course** cancelReg, std::string sem, unsigned __int64 stuID) {
	if (cancelReg == nullptr) return;
	int n = _msize(cancelReg) / sizeof(cancelReg);
	for (int i = 0; i < n; i++) {
		int n = 0;
		for (int j = 0; j < cancelReg[i]->maxstudent; j++) {
			if (cancelReg[i]->stuID[j] == stuID) {
				n = j;
				break;
			}
		}
		cancelReg[i]->numberofstudent -= 1;
		cancelReg[i]->stuID[n] = cancelReg[i]->stuID[cancelReg[i]->numberofstudent];
		CourseToBin(cancelReg[i], cancelReg[i]->ID, sem);
		char* accountID = StrToChar(NumToStr(stuID));
		SaveCourseCancelHis(accountID, *cancelReg[i]);
		delete[]accountID;
	}
}
void registerCourse(Student* stu, Course** cou, std::string sem) {
	int semester = sem[sem.length() - 1] - '0';
	char y[5];
	sem.copy(y, 4, sem.length() - 14);
	y[4] = '\0';
	int year = StringToInt(y);
	int n = 0;
	for (int i = 0; i < 5; i++) {
		if (cou[i] == nullptr) {
			n = i;
			break;
		}
	}
	stu->coursenow = new char* [n];
	std::string temp;
	for (int i = 0; i < n; i++) {
		temp = ToString(cou[i]->ID) + ToString(y) + std::to_string(semester);
		stu->coursenow[i] = StrToChar(temp);
	}
	StuToBin(stu, GetFilePath(stu->ID));
}
bool isConflict(Course* a, Course* b)		// true means conflict, false is not
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (a->performed[i].day == b->performed[j].day)
			{
				if (a->performed[i].session == b->performed[j].session)
					return 1;
			}
		}
	}
	return 0;
}
void SessionConflict(Course** a, Course** b, int*& Register)
{
	int n = _msize(a) / sizeof(a);

	for (int i = 0; i < n; i++)
	{
		Register[i] = 0;
		for (int j = 0; j < 5; j++)
		{
			if (b[j] == nullptr) break;
			if (a[i] == b[j])
			{
				Register[i] = 1;
				break;
			}
			if (isConflict(a[i], b[j]))
			{
				Register[i] = -1;
				break;
			}

		}
	}

}
void classifyCourse(Course** reg, Course** wasReg, Course**& cancelReg, Course**& newReg)
{
	int n = 0;
	int m = 0;

	for (int i = 0; i < 5; i++) {
		if (reg[i] == nullptr) {
			n = i; break;
		}
	}

	if (wasReg != nullptr) m = _msize(wasReg) / sizeof(wasReg);
	if (m + n == 0) return;
	int* a = new int[n + m];
	int* b = new int[n + m];
	int N = 0;
	int M = 0;
	for (int i = 0; i < n; i++)
	{
		bool check = 0;
		for (int j = 0; j < m; j++)
		{
			if (reg[i] == wasReg[j])
			{
				check = 1;
				break;
			}
		}
		if (!check)
		{
			a[N] = i;
			N += 1;
		}
	}

	for (int j = 0; j < m; j++)
	{
		bool check = 0;
		for (int i = 0; i < n; i++)
		{
			if (wasReg[j] == reg[i])
			{
				check = 1;
				break;
			}
		}
		if (!check)
		{
			b[M] = j;
			M += 1;
		}
	}

	if (N > 0) newReg = new Course * [N];
	if (M > 0) cancelReg = new Course * [M];
	for (int i = 0; i < N; i++)
		newReg[i] = reg[a[i]];
	for (int i = 0; i < M; i++)
		cancelReg[i] = wasReg[b[i]];
	delete[] a;
	delete[] b;
}

//**************Student****************

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
		if (toupper(temp1[1]) == 'A' || toupper(temp[1] == 'E'))
			stu->gender = 'M';
		do {
			std::cout << "Birth(dd/mm/yy): "; stu->birth = InputDate();
		} while (CheckDate(stu->birth) == false);
		std::cin.ignore(1000, '\n');
		std::cout << "Social ID: "; std::cin >> stu->SocialID;

		stu->account.username = StrToChar(NumToStr(stu->ID));
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
	} while (choose == 0);
	DealocatedArrString(chooselist);
	delete[] chooselist;
	return result;
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
_Student* SearchStuList(unsigned __int64* ID) // Return LL _Student		// Use dynamic array of ID when using
{
	_Student* head = nullptr, * cur;
	head = new _Student;	// dummy node;
	cur = head;
	head->pNext = head->pPrev = nullptr;
	int n = _msize(ID) / 8;
	for (int i = 0; i < n; i++)
	{
		std::string id = NumToStr(ID[i]);
		std::string foldername = "K20";
		foldername = foldername + id[0] + id[1];
		Student* temp = BinToStu("Data\\Grade\\" + foldername + "\\Student\\" + id);
		if (temp != nullptr)
		{
			cur->pNext = new _Student;
			cur->pNext->pPrev = cur;
			cur = cur->pNext;
			cur->student = BinToStu("Data\\Grade\\" + foldername + "\\Student\\" + id);
			cur->pNext = head;
			head->pPrev = cur;
			deleteStu(temp);
		}
	}
	_Student* temp = head;
	head = head->pNext;
	cur->pNext = head;
	if (head)
		head->pPrev = cur;
	delete temp;	//delete dummy node
	return head;
	// REMEMBER TO DEALLOCATE WHEN FINISHED SEARCHING !!!
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
	stu->coursenow = nullptr;

	if (k > 0) stu->coursenow = new char* [k];
	for (int i = 0; i < k; i++) {
		int e = 0;
		fi.read((char*)&e, sizeof(int));
		stu->coursenow[i] = new char[e];
		fi.read(stu->coursenow[i], e);
	}

	fi.read((char*)&k, sizeof(int));
	if (k > 0) stu->allcourse = new char* [k];
	else { stu->allcourse = nullptr; }
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
	//RemoveSpace(stu->firstname);

	beg = end + 1;
	end = str.find(L',', beg);
	stu->lastname = new wchar_t[end - beg + 1];
	stu->lastname[end - beg] = L'\0';
	str.copy(stu->lastname, end - beg, beg);
	//RemoveSpace(stu->lastname);

	beg = end + 1;
	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	if (wcscmp(temp, L"Nam") == 0 || wcscmp(temp, L"Men")==0)stu->gender = 'M';
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
Student* SearchStu(unsigned __int64 ID)
{
	std::string id = NumToStr(ID);
	std::string foldername = "K20";
	foldername = foldername + id[0] + id[1];
	Student* a = BinToStu("Data\\Grade\\" + foldername + "\\Student\\" + id);
	if (!a)
		std::cout << ID << " does not exist " << std::endl;
	return a;
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
Student** SearchStuArr(unsigned __int64* ID, std::string Grade)	// Use dynamic array of ID when using
{
	Student** a = nullptr;
	int n = _msize(ID) / 8;
	a = new Student * [n] {};
	for (int i = 0; i < n; i++)
	{
		a[i] = BinToStu("Data\\Grade\\" + Grade + "\\Student\\" + NumToStr(ID[i]));
		if (a[i] == nullptr)
		{
			std::cout << ID[i] << " does not exist " << std::endl;
		}
	}
	return a;

	// REMEMBER TO DEALLOCATE WHEN FINISHED SEARCHING !!!
}
std::string GetFilePath(unsigned __int64 ID)
{
	std::string foldername = "K20";
	foldername = foldername + NumToStr(ID)[0] + NumToStr(ID)[1];
	std::string path = "Data\\Grade\\" + foldername + "\\Student\\" + NumToStr(ID);
	Student* a = BinToStu(path);
	if (a)
	{
		deleteStu(a);
		return path;
	}
	else return "";
}

void SaveNewStu(_Student* stu, char* direction) {
	if (stu == nullptr) return;
	char* direc = StrCat(direction, "\\Student\\");
	_Student* temp = stu;
	do {
		char* filename = StrToChar(NumToStr(stu->student->ID));
		char* fileout = AddTwoStr(direc, filename);
		StuToBin(stu->student, fileout);
		delete[] filename;
		delete[] fileout;
		stu = stu->pNext;
	} while (stu != temp);
	delete[] direc;
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
	else k = _msize(stu->coursenow) / sizeof(stu->coursenow);
	fo.write((char*)&k, sizeof(int));
	for (int i = 0; i < k; i++) {
		int e = _msize(stu->coursenow[i]) / sizeof(char) + 1;
		fo.write((char*)&e, sizeof(int));
		fo.write(stu->coursenow[i], e);
	}
	if (stu->allcourse == nullptr) k = 0;
	else k = _msize(stu->allcourse) / sizeof(stu->allcourse);
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
void AddStudent(_Student*& studentlist, Student* student) {
	if (studentlist == nullptr) { studentlist = new _Student{ student }; studentlist->pNext = studentlist, studentlist->pPrev = studentlist; return; }
	studentlist->pPrev = new _Student{ student,studentlist,studentlist->pPrev };
	studentlist->pPrev->pPrev->pNext = studentlist->pPrev;
}
void removeAcourseForStudents(int* studentsIDs, char* courseID) {
	int size = sizeof(studentsIDs) / sizeof(studentsIDs);
	for (int i = 0; i < size; i++) {
		Student* s = SearchStu(studentsIDs[i]);
		int sizeCourse = sizeof(s->coursenow) / sizeof(s->coursenow);
		for (int j = 0; j < sizeCourse; j++) {
			if (s->coursenow[j] == courseID) {
				delete[] s->coursenow[j];
				if (sizeCourse != 1)s->coursenow[j] = s->coursenow[sizeCourse - 1];
				break;
			}
		}
		if (sizeCourse != 1) {
			char** temp = s->coursenow;
			s->coursenow = new char* [sizeCourse - 1];
			for (int i = 0; i < sizeCourse - 1; i++) {
				s->coursenow[i] = temp[i];
			}
			delete[] temp;
		}
		else s->coursenow = nullptr;
		StuToBin(s, GetFilePath(s->ID));
		deleteStu(s);
	}

}

//**************Classes****************
Classes MakeClass(_Student*& all, bool cls, int x, int y) {
	if (cls) system("cls");
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
			//sort
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
void AddClass(_Class*& cls, Classes sourse) {
	if (cls == nullptr) {
		cls = new _Class{ sourse };
		cls->pNext = cls;
		cls->pPrev = cls;
		return;
	}
	cls->pPrev = new _Class{ sourse,cls,cls->pPrev };
	cls->pPrev->pPrev->pNext = cls->pPrev;
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
void SaveClass(Classes cl, const char* fileout) {
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
void PrintClass(Classes a) {
	_SText();
	std::cout << a.name << '\n';
	int n = _msize(a.ID) / sizeof(__int64);
	if (a.ID != nullptr) {
		for (int i = 0; i < n; i++) {
			std::cout << a.ID[i] << '\n';
		}
	}
}

//**************FileList***************
int CountFile(Filelist* list) {
	if (list == nullptr) return 0;
	Filelist* flag = list;
	int num = 0;
	do {
		num += 1;
		list = list->pNext;
	} while (list != flag);
	return num;
}
Filelist* TakeFileInFolder(const std::wstring& name)
{
	Filelist* result = nullptr;
	std::wstring pattern(name);
	pattern.append(L"\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			if (!(wcscmp(data.cFileName, L".") == 0 || wcscmp(data.cFileName, L"..") == 0)) AddInListFile(result, ToString(data.cFileName));
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
	return result;
}
Filelist* TakeFileInFolder(const std::string& name) {
	return TakeFileInFolder(ToWstring(name));
}
std::string ChoseFolder(Filelist* list, short x, short y) {
	if (list == nullptr) return"";
	Filelist* temp = list;
	int i = 0;
	do {
		GotoXY(x, y + i); std::cout << temp->filename;
		i += 1;
		temp = temp->pNext;
	} while (list != temp);
	i = 0;
	int n = CountFile(list) - 1;
	GotoXY(x, y); std::cout << "> " << temp->filename << " <";
	char get = 0;
	while (true)
	{
		get = _getwch();
		get = toupper(get);
		if (get == 'W' || get == KEY_UP) {
			GotoXY(x, y + i); std::cout << temp->filename << "    ";
			temp == list ? i = n : i -= 1;
			temp = temp->pPrev;
			GotoXY(x, y + i); std::cout << "> " << temp->filename << " <";
		}
		else if (get == 'S' || get == KEY_DOWN) {
			GotoXY(x, y + i); std::cout << temp->filename << "    ";
			temp == list->pPrev ? i = 0 : i += 1;
			temp = temp->pNext;
			GotoXY(x, y + i); std::cout << "> " << temp->filename << " <";
		}
		else if (get == KEY_ENTER || get == ' ') {
			return temp->filename;
		}
		else if (get == KEY_ESC) {
			return "";
		}
	}
}
void DeleteCurFileList(Filelist*& filelist) {
	if (filelist->pNext == filelist) {
		delete filelist;
		filelist = nullptr;
	}
	else {
		Filelist* filedel = filelist;
		filelist = filelist->pNext;
		filedel->pPrev->pNext = filedel->pNext;
		filedel->pNext->pPrev = filedel->pPrev;
		delete filedel;
	}
}
void AddInListFile(Filelist*& direc, std::string add) {
	if (direc == nullptr) { direc = new Filelist{ add }; direc->pNext = direc, direc->pPrev = direc; return; }
	direc->pPrev = new Filelist{ add,direc,direc->pPrev };
	direc->pPrev->pPrev->pNext = direc->pPrev;
}

//****************Delete Struct**************
void deleteStu(Student*& a)
{
	if (a == nullptr) return;
	delete[]a->account.password;
	delete[]a->account.username;
	delete[]a->firstname;
	delete[]a->lastname;
	if (a->coursenow)
	{
		int n = _msize(a->coursenow) / sizeof(a->coursenow);
		for (int i = 0; i < n; i++)
			delete[]a->coursenow[i];
		delete[]a->coursenow;
	}
	if (a->allcourse)
	{
		int n = _msize(a->allcourse) / sizeof(a->allcourse);
		for (int i = 0; i < n; i++)
			delete[]a->allcourse[i];
		delete[]a->allcourse;
	}
	delete a;
	a = nullptr;
}
void deleteStu(Student**& a) {
	if (a == nullptr) return;
	int n = _msize(a) / sizeof(a);
	for (int i = 0; i < n; i++) {
		deleteStu(a[i]);
	}
	delete[] a;
	a = nullptr;
}
void delete_Stu(_Student*& a)
{
	if (a == nullptr)
		return;
	_Student* cur = a->pNext;
	while (cur != a)	// Deallocate Second Node afterwards
	{
		_Student* temp = cur;
		cur = cur->pNext;
		deleteStu(temp->student);
		delete temp;
	}
	deleteStu(cur->student);		// Deallocate First Node 
	delete cur;
	a = nullptr;
}
void deleteCourse(Course*& a)
{
	if (a == nullptr) return;
	delete[]a->ID;
	delete[]a->name;
	delete[]a->teacher;
	if (a->stuID)
		delete[]a->stuID;
	if (a->score)
	{
		int n = _msize(a->score) / sizeof(*a->score);
		for (int i = 0; i < n; i++) {
			delete[] a->score[i].name;
		}
		delete a->score;
	}
	delete a;
	a = nullptr;
}
void deleteCourse(Course**& a) {
	if (a == nullptr) return;
	int n = _msize(a) / sizeof(a);
	for (int i = 0; i < n; i++) {
		deleteCourse(a[i]);
	}
	delete[] a;
}
void delete_Course(_Course*& a)
{
	if (a == nullptr)
		return;
	_Course* cur = a->pNext;
	while (cur != a)	// Deallocate Second Node afterwards
	{
		_Course* temp = cur;
		cur = cur->pNext;
		deleteCourse(temp->course);
		delete temp;
	}
	deleteCourse(cur->course);		// Deallocate First Node 
	delete cur;
	a = nullptr;
}
void deleteClasses(Classes*& a)
{
	if (a == nullptr) return;
	delete[]a->name;
	delete[]a->ID;
	delete a;
	a = nullptr;
}

void deleteClasses(Classes**& a) {
	if (a == nullptr) return;
	int n = _msize(a) / sizeof(a);
	for (int i = 0; i < n; i++) {
		deleteClasses(a[i]);
	}
	delete[] a;
	a = nullptr;
}

void deleteClasses(Classes& a)
{
	delete[]a.name;
	delete[]a.ID;
}
void delete_Class(_Class*& a)
{
	if (a == nullptr)
		return;
	_Class* cur = a->pNext;
	while (cur != a)	// Deallocate Second Node afterwards
	{
		_Class* temp = cur;
		cur = cur->pNext;
		delete temp;
	}
	// Deallocate First Node 
	delete cur;
	a = nullptr;
}
void deleteSemester(Semester* a)
{
	delete_Course(a->course);
	delete a;
}
void deleteSchoolyear(SchoolYear*& a)
{
	int n = _msize(a->semester) / sizeof(a->semester);
	for (int i = 0; i < n; i++) {
		deleteSemester(&a->semester[i]);
	}
	delete_Class(a->classes);
	delete_Stu(a->student);
	delete a;
}
void deleteFilelist(Filelist*& a)
{
	if (a == nullptr)
		return;
	Filelist* cur = a->pNext;
	while (cur != a)	// Deallocate Second Node afterwards
	{
		Filelist* temp = cur;
		cur = cur->pNext;
		delete temp;
	}
	// Deallocate First Node 
	delete cur;
	a = nullptr;
}
void deleteIntArray(int*& a)
{
	delete[]a;
}
void deleteIntArray(unsigned __int64*& a)
{
	delete[]a;
	a = nullptr;
}
void deleteStuArray(Student**& a)
{
	if (a == nullptr)
		return;
	int n = _msize(a) / sizeof(a);
	for (int i = 0; i < n; i++)
	{
		if (a[i])
			deleteStu(a[i]);
	}
	delete[]a;
	a = nullptr;
}