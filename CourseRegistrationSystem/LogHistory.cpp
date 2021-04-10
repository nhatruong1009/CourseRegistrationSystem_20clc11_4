#include"CommonFunc.h"
#include"Data.h"

void SaveLogoutHistory(char* AccountUsername)
{
	__time32_t now = time(0);
	char a[100];
	_ctime32_s(a, &now);
	std::ofstream file;
	file.open("logout.txt", std::ios::app);
	file << AccountUsername << " " << a;
	file.close();
}

void SaveCourseRegHis(char* AccountUsername)
{
	__time32_t now = time(0);
	char a[100];
	_ctime32_s(a, &now);
	std::ofstream file;
	file.open("coursereg.txt", std::ios::app);
	file << AccountUsername << " " << a;
	file.close();
}

void SaveCourseCancelHis(char* AccountUsername)
{
	__time32_t now = time(0);
	char a[100];
	_ctime32_s(a, &now);
	std::ofstream file;
	file.open("coursecancel.txt", std::ios::app);
	file << AccountUsername << " " << a;
	file.close();
}