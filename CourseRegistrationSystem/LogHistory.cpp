#include"CommonFunc.h"
#include"Data.h"


std::string InputPass() {
	char temp;
	std::string pass;
	while (true)
	{
		temp = _getwch();
		if (temp == KEY_ENTER) break;
		else if (temp == KEY_ESC) return "";
		if (temp == KEY_BACKSPACE) {
			if (pass.size() != 0) {
				pass.pop_back();
				std::cout << temp << ' ' << temp;
			}
		}
		if (temp>=' ' && temp<='~'){
			std::cout << "*";
			pass.push_back(temp);
		}
	}
	return pass;
}

void ChangeInfo(Student* CurrentUser);
void SaveLogoutHistory(char* AccountUsername)
{
	__time32_t now = time(0);
	char a[100];
	_ctime32_s(a, &now);
	std::ofstream file;
	file.open("History\\logout.txt", std::ios::app);
	file << AccountUsername << " " << a;
	file.close();
}

void SaveCourseRegHis(char* AccountUsername, Course course)
{
	__time32_t now = time(0);
	char a[100];
	_ctime32_s(a, &now);
	std::ofstream file;
	file.open("History\\coursereg.txt", std::ios::app);
	file << AccountUsername << " " << course.ID << " " << a;
	file.close();
}

void SaveCourseCancelHis(char* AccountUsername, Course course)
{
	__time32_t now = time(0);
	char a[100];
	_ctime32_s(a, &now);
	std::ofstream file;
	file.open("History\\coursecancel.txt", std::ios::app);
	file << AccountUsername << " " << course.ID << " " << a;
	file.close();
}

void LoginStu(Student*& CurrentUser)
{
	system("cls");	//clear the screen
	std::string U, P;
	if (std::cin.tellg() != 0) { std::cin.ignore(1i64, '\n'); }
	do
	{
		std::cout << "----------- Login -----------\n";
		std::cout << "Username: ";
		std::getline(std::cin, U);
		std::cout << "Password: ";
		//std::getline(std::cin, P);
		P = InputPass();
		if (P == "") { CurrentUser = 0; break; }// don't input password;
		std::string foldername = "K20";
		foldername = foldername + U[0] + U[1];
		Filelist* list = TakeFileInFolder("Data\\Grade\\" + foldername + "\\Student");
		if (list == nullptr)
		{
			system("cls");
			std::cout << "Username is invalid, please try again." << std::endl;
			continue;
		}
		Filelist* cur = list;
		// Read Account File
		do
		{
			if (U == ToString(cur->filename))
				break;
			cur = cur->pNext;
		} while (cur != list);
		if (U != ToString(cur->filename))
		{
			system("cls");
			std::cout << "Username is invalid, please try again." << std::endl;
			continue;
		}
		Student a = BinToStu("Data\\Grade\\" + foldername + "\\Student\\" + ToString(cur->filename));
		if (P.compare(ToString(a.account.password)) == 0)
		{
			CurrentUser = new Student{ a };
			SaveLoginHistory(a.account.username);
			break;
		}
		else { system("cls"); std::cout << "Password is invalid, please try again. " << std::endl; }
	} while (1);
	// Go to Student menu
}

void Logout(Student CurrentUser)
{
	system("cls");
	SaveLogoutHistory(CurrentUser.account.username);
	// Go to menu
}

void ChangePassword(Student* CurrentUser)
{

	system("cls");
	std::string pass1, pass2;
	do
	{
		std::cout << "\nNew password: \t\t\t";
		pass1 = InputPass();
		std::cout << "\nConfirm password: \t\t";
		pass2 = InputPass();
		if (pass1 != pass2) std::cout << "\nYour password and confirmation password do not match, try again." << std::endl << std::endl;
	} while (pass1 != pass2);
	std::string foldername = "K20"; // 21st century, will update later when 22nd century come
	foldername = foldername + CurrentUser->account.username[0] + CurrentUser->account.username[1];
	CurrentUser->account.password = StrToChar(pass1);
	StuToBin(CurrentUser, "Data\\Grade\\" + foldername + "\\Student\\" + ToString(CurrentUser->account.username));
	short n;
	std::cout << "\nChange successfully " << std::endl;
	std::cout << "> Go back <";
	_getwch();
	ChangeInfo(CurrentUser);
}

void ChangeSocialID(Student* CurrentUser)
{
	system("cls");
	unsigned __int64 newSocialID1, newSocialID2;
	do
	{
		std::cout << "New Social ID: ";
		std::cin >> newSocialID1;
		std::cout << "Confirm new Social ID: ";
		std::cin >> newSocialID2;
		if (newSocialID1 != newSocialID2)
			std::cout << "New Social ID and Confirm Social ID do not match, try again " << std::endl << std::endl;
	} while (newSocialID1 != newSocialID2);
	std::cout << "Change succesfully " << std::endl;
	CurrentUser->SocialID = newSocialID1;
	std::string foldername = "K20"; // 21st century, will update later when 22nd century come
	foldername = foldername + CurrentUser->account.username[0] + CurrentUser->account.username[1];
	StuToBin(CurrentUser, "Data\\Grade\\" + foldername + "\\Student\\" + ToString(CurrentUser->account.username));
	short n;
	do
	{
		std::cout << "Enter 0 to go back ";
		std::cin >> n;
	} while (n != 0);
	ChangeInfo(CurrentUser);
}

bool LeapYear(int y)
{
	if (y % 400 == 0)
		return 1;
	else if (y % 4 == 0 && y % 25 != 0)
		return 1;
	return 0;
}

bool CheckDate(int d, int m, int y)
{
	if (d < 1 || m < 1 || y < 0)
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

void ChangeDOB(Student* CurrentUser)
{
	system("cls");
	unsigned int d, m, y;
	while (1)
	{
		std::cout << "Day: ";
		std::cin >> d;
		std::cout << "Month: ";
		std::cin >> m;
		std::cout << "Year: ";
		std::cin >> y;
		if (CheckDate(d, m, y))
			break;
		else
		{
			std::cout << "Date is invalid, try again. " << std::endl << std::endl;
			continue;
		}
	}
	std::cout << "Change successfully " << std::endl;
	CurrentUser->birth.dd = d;
	CurrentUser->birth.mm = m;
	CurrentUser->birth.yy = y;
	std::string foldername = "K20"; // 21st century, will update later when 22nd century come
	foldername = foldername + CurrentUser->account.username[0] + CurrentUser->account.username[1];
	StuToBin(CurrentUser, "Data\\Grade\\" + foldername + "\\Student\\" + ToString(CurrentUser->account.username));
	short n;
	do
	{
		std::cout << "Enter 0 to go back ";
		std::cin >> n;
	} while (n != 0);
	ChangeInfo(CurrentUser);
}

void ChangeInfo(Student* CurrentUser)
{
	system("cls");
	int num;
	char** menu = new char* [4];
	menu[0] = new char[] {"Password"};
	menu[1] = new char[] {"Date Of Birth"};
	menu[2] = new char[] {"Social ID"};
	menu[3] = new char[] {"Back"};
	switch (Menu(menu, 5, 2))
	{
	case 0:
		ChangePassword(CurrentUser);
		break;
	case 1:
		ChangeDOB(CurrentUser);
		break;
	case 2:
		ChangeSocialID(CurrentUser);
		break;
	case 3:
	case -1:

		return;
		// return to student mode
	}
}

_Student* Search(unsigned __int64 ID[])
{
	_Student* head = nullptr, * cur;
	head = new _Student;	// dummy node;
	cur = head;
	head->pNext = head->pPrev = nullptr;
	int n = sizeof(ID) / 8;
	for (int i = 0; i < n; i++)
	{
		std::string id = ToString(NumToStr(ID[i]));
	}
	cur = nullptr;
	_Student* temp = head;
	head = head->pNext;
	delete temp;	//delete dummy node
	return head;
}