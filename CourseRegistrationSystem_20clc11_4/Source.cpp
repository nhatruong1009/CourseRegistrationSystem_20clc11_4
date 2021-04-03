#include"CommonFunc.h"

using namespace std;

int main() {
	std::string fi;
	std::cin >> fi;
	_Student* a = FileInStudent(fi);
	PrintStu(a);
}