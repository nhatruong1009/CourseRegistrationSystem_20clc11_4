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
	std::string U, P;
	Filelist* list = TakeFileInFolder("Data\\K2021\\Student");
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
			if (U == cur->filename)
				break;
			cur = cur->pNext;
		} while (cur != list);
		if (U != cur->filename)
		{
			std::cout << "Username is invalid, please try again." << std::endl;
			continue;
		}
		Student a = BinToStu("Data\\K2021\\Student\\" + cur->filename);
		if (P == ToString(a.account.password))
			break;
		else std::cout << "Password is invalid, please try again. " << std::endl;
	} while (1);
	std::cout << "Successful";
	// Go to Student menu
}