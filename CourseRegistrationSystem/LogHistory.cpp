#include"CommonFunc.h"
#include"Data.h"

void SaveLogoutHistory(char* AccountUsername)
{
	__time32_t now = time(0);
	char a[100];
	_ctime32_s(a, &now);
	std::ofstream file;
	file.open("logout.txt", std::ios::app);
	file << AccountUsername << " " << a << std::endl;
	file.close();
}