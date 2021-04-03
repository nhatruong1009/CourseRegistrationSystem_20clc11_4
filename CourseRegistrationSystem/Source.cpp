#include"CommonFunc.h"
#include"Data.h"
#include<locale>
#include<codecvt>
using namespace std;



int main() {
	string file;
	cin >> file;
	_Student* a = FileInStudent(file);
	PrintStu(a);
	cin >> file;
	_Student* b=nullptr;
	StuToBin(a, file);
	BinToStu(b, file);
	PrintStu(b);
}