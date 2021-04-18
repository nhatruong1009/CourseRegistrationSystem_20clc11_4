#include"CommonFunc.h"
#include"Data.h"

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
	Filelist* list = TakeFileInFolder("Data\\K2021\\Student");// cai nay hoi sai , minh phai lay 2 so dau tien cua mssv de loc file
	do
	{
		Filelist* cur = list;
		std::cout << "Username: ";
		std::cin >> U;
		std::cout << "Password: ";
		std::cin >> P;
		// Read Account File
		// 2 file dau co ten la "." voi "..", lay du file???
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
		Student a = BinToStu("Data\\K2021\\Student\\" + ToString(cur->filename));
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
		if (pass1 != pass2) std::cout << "Your password and confirmation password do not match, please try again." << std::endl;
	} while (pass1 != pass2);
	CurrentUser.account.password = StrToChar(pass1);
	StuToBin(&CurrentUser, "Data\\K2021\\Student\\" + ToString(CurrentUser.account.username));
	short n;
	do
	{
		std::cout << "Enter 0 to go back ";
		std::cin >> n;
	} while (n != 0);
	// Go back to Student menu
}

void ChangeSocialID(Student CurrentUser)
{
	unsigned __int64 newSocialID1, newSocialID2;
	do
	{
		std::cout << "New Social ID: ";
		std::cin >> newSocialID1;
		std::cout << "Confirm new Social ID: ";
		std::cin >> newSocialID2;
	} while (newSocialID1 != newSocialID2);
	CurrentUser.SocialID = newSocialID1;
	StuToBin(&CurrentUser, "Data\\K2021\\Student\\" + ToString(CurrentUser.account.username));
	short n;
	do
	{
		std::cout << "Enter 0 to go back ";
		std::cin >> n;
	} while (n != 0);
	// Go back to Student menu
}

void ChangeInfo(Student CurrentUser)
{
	system("cls");
	int num;
	std::cout << "Change information" << std::endl;
	std::cout << "Choose "<<std::endl;
	std::cout << "0. Go back ";
	std::cout << "1. Social ID ";
	std::cin >> num;
	switch (num)
	{
	case 0: // Go to Student menu
	case 1: 
		ChangeSocialID(CurrentUser);
		break;
	}
}