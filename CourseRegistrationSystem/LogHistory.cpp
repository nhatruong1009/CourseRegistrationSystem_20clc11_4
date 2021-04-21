#include"CommonFunc.h"
#include"Data.h"
void ChangeInfo(Student CurrentUser);
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
	file << AccountUsername << " "<<course.ID<<" " << a;
	file.close();
}

void SaveCourseCancelHis(char* AccountUsername, Course course)
{
	__time32_t now = time(0);
	char a[100];
	_ctime32_s(a, &now);
	std::ofstream file;
	file.open("History\\coursecancel.txt", std::ios::app);
	file << AccountUsername << " "<<course.ID<<" " << a;
	file.close();
}

void LoginStu(Student& CurrentUser)
{
	system("cls");	//clear the screen
	std::string U, P;
	do
	{
		std::cout << "Username: ";
		std::cin >> U;
		std::cout << "Password: ";
		std::cin >> P;
		std::string foldername = "K20"; // 21st century, will update later when 22nd century come
		foldername = foldername + U[0] + U[1];
		Filelist* list = TakeFileInFolder("Data\\Grade\\" + foldername + "\\Student");
		if (list == nullptr)
		{
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
			std::cout << "Username is invalid, please try again." << std::endl;
			continue;
		}
		Student a = BinToStu("Data\\Grade\\" + foldername + "\\Student\\" + ToString(cur->filename));
		if (P == ToString(a.account.password))
		{
			CurrentUser = a;
			SaveLoginHistory(a.account.username);
			break;
		}
		else std::cout << "Password is invalid, please try again. " << std::endl;
	} while (1);
	std::cout << "Successful";
	// Go to Student menu
}

void Logout(Student CurrentUser)
{
	system("cls");
	SaveLogoutHistory(CurrentUser.account.username);
	// Go to menu
}

void ChangePassword(Student CurrentUser)
{
	system("cls");
	std::string pass1, pass2;
	do
	{
		std::cout << "New password: ";
		std::cin >> pass1;
		std::cout << "Confirm password: ";
		std::cin >> pass2;
		if (pass1 != pass2) std::cout << "Your password and confirmation password do not match, try again." << std::endl << std::endl;
	} while (pass1 != pass2);
	std::string foldername = "K20"; // 21st century, will update later when 22nd century come
	foldername = foldername + CurrentUser.account.username[0] + CurrentUser.account.username[1];
	CurrentUser.account.password = StrToChar(pass1);
	StuToBin(&CurrentUser, "Data\\Grade\\" + foldername + "\\Student\\" + ToString(CurrentUser.account.username));
	short n;
	std::cout << "Change successfully " << std::endl;
	do
	{
		std::cout << "Enter 0 to go back ";
		std::cin >> n;
	} while (n != 0);
	ChangeInfo(CurrentUser);
}

void ChangeSocialID(Student CurrentUser)
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
	CurrentUser.SocialID = newSocialID1;
	std::string foldername = "K20"; // 21st century, will update later when 22nd century come
	foldername = foldername + CurrentUser.account.username[0] + CurrentUser.account.username[1];
	StuToBin(&CurrentUser, "Data\\Grade\\" + foldername + "\\Student\\" + ToString(CurrentUser.account.username));
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

void ChangeDOB(Student CurrentUser)
{
	system("cls");
	unsigned int d, m, y;
	while(1)
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
			std::cout << "Date is invalid, try again. "<<std::endl<<std::endl;
			continue;
		}
	} 
	std::cout << "Change successfully " << std::endl;
	CurrentUser.birth.dd = d;
	CurrentUser.birth.mm = m;
	CurrentUser.birth.yy = y;
	std::string foldername = "K20"; // 21st century, will update later when 22nd century come
	foldername = foldername + CurrentUser.account.username[0] + CurrentUser.account.username[1];
	StuToBin(&CurrentUser, "Data\\Grade\\" + foldername + "\\Student\\" + ToString(CurrentUser.account.username));
	short n;
	do
	{
		std::cout << "Enter 0 to go back ";
		std::cin >> n;
	} while (n != 0);
	ChangeInfo(CurrentUser);
}

void ChangeInfo(Student CurrentUser)
{
	system("cls");
	int num;
	std::cout << "Change information" << std::endl;
	std::cout << "Choose " << std::endl;
	std::cout << "1. Password " << std::endl;
	std::cout << "2. Social ID " << std::endl;
	std::cout << "3. Date of Birth " << std::endl;
	std::cout << "0. Go back " << std::endl;
	std::cin >> num;
	switch (num)
	{
	case 0: break; // Go to Student menu
	case 1:
		ChangePassword(CurrentUser);
		break;
	case 2:
		ChangeSocialID(CurrentUser);
		break;
	case 3:
		ChangeDOB(CurrentUser);
		break;
	}
}