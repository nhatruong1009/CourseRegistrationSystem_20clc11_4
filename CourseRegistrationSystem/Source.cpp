#include"CommonFunc.h"
#include"Data.h"
#include<locale>
#include<codecvt>
using namespace std;

int main() {
	string fi;
	cin >> fi;
	_Student* a = nullptr;
	int t1 = time(0);
	a = FileInStudent(fi);
	int t2 = time(0);
	double k = time(0);
	cout << t2 - t1;
	cin >> fi;
	StuToBin(a, fi);
	cout << "done\n";
	cin >> fi;
	int e = time(0);
	BinToStu(a, fi);
	int f = time(0);
//	cout << "done\n";
	_SText();
	cout << f - e;
}