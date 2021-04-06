#include"CommonFunc.h"
#include"Data.h"
#include<locale>
#include<codecvt>
using namespace std;

int main(int argc, char*argv[] ) {
	cout << argv[0]<<'\n';
	system("explorer /select,\"student\\\"");
	fstream fi ("student.txt",fstream::out);

}