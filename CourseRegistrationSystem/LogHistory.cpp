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

void LoginStu()
{
	system("cls");	//clear the screen
	char* U, *P;
	U = new char[50];
	P = new char[50];
	Filelist* list = TakeFileInFolder("Data\\K2021\\Student");
	Filelist* cur = list;
	do
	{
		std::cout << "Username: ";
		std::cin >> U;
		std::cout << "Password: ";
		std::cin >> P;
		// Read Account File
		do
		{
		if (*U != *StrToChar(cur->filename))
			break;
			cur = cur->pNext;
		} while (cur != list);
		if (*U != *StrToChar(cur->filename))
		{
			std::cout << "Username is invalid, please try again.";
			continue;
		}
		Student a = BinToStu("Data\\K2021\\Student\\" + list->filename);
		if (*P == *a.account.password)
			break;
		else
		{
			std::cout << "Password is invalid, please try again.";
		}
	} while (1);
	delete[]U;
	delete[]P;
	// Go to Student menu
}