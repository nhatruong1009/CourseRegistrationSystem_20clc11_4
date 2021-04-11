#include"CommonFunc.h"
#include"Data.h"
#include<locale>
#include<codecvt>
#include<string>

#include<conio.h>
using namespace std;
 


int main(int argc, char* argv[]) {
	SchoolYear*a= AddSchoolYear();
	SaveSchoolYear(a,"year.txt");
	cout << "end";
}