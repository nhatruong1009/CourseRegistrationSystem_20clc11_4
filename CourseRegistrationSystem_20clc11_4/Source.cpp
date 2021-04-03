#include"CommonFunc.h"
#include"Data.h"
#include<fstream>;
using namespace std;


int main() {
	std::string fi;
	std::cin >> fi;
<<<<<<< Updated upstream
	_Student* a = FileInStudent(fi);
	PrintStu(a);
	std::cin >> fi;
	FileOutStudent(a, fi);
=======
	std::fstream fo(fi, std::fstream::in | std::fstream::binary);

	wchar_t* k;
	char* temp = new char[17 * 2];
	fo.read(temp, 17 * 2);
	k = (wchar_t*)temp;
	_LText();
	std::wcout << wcslen(k);
>>>>>>> Stashed changes
}