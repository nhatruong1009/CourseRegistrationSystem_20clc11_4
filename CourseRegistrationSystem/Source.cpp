#include <windows.h>
#include<iostream>
#include<vector>
#include<string>
#include"CommonFunc.h"
void main() {

    Filelist* a =TakeFileInFolder("Data\\K2021\\Student");
    Filelist* b = a;
    do {
        std::cout << a->filename<<'\n';
        a = a->pNext;
    } while (a != b);
}