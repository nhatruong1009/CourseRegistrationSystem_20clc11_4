#include"CommonFunc.h"
#include"Data.h"
#include<locale>
#include<codecvt>
#include<string>
using namespace std;

int main(int argc, char*argv[] ) {
	string filein;
	cin >> filein;
	fstream fi(filein, fstream::in);
	fi.seekg(-1, ios_base::end);
	int last = fi.tellg();
	fi.seekg(0, ios_base::beg);
	string temp;
	_Student* stu = nullptr;
	while (fi.tellg()<last)
	{
		Student uwu;
		getline(fi, temp, ' ');
		getline(fi, temp, '\n');
		uwu= BinToStu(temp);
		PrintStu(&uwu);
		AddStudent(stu, uwu);
	}
	fi.close();
	//PrintStu(stu);
}