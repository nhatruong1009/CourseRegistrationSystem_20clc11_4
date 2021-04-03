#include"CommonFunc.h"
#include"Data.h"
#include<locale>
#include<codecvt>
using namespace std;



int main() {
	std::string fi;
	std::cin >> fi;
	_Student* a = FileInStudent(fi);
	PrintStu(a);
	std::cin >> fi;
	FileOutStudent(a, fi);

}