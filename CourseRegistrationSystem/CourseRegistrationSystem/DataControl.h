#ifndef DataControl
#define DataControl
#include"NewStructs.h"

void VietNamText();
void LoadClassInfo(_Class*& classes);
void LoadCourseInfo(_Course*& course);
void LoadScoreBoard(Score*& scoreboard);
void LoadYear(SchoolYear*& year);
void SaveStudent(_Student* stu, std::wstring filename);
_Student* LoadStudent(std::wstring filename);
void SaveClassInfo(_Class* classes);
void SaveCourseInfo(_Course* course);
void SaveScoreBoar(Score* scoreboard);
void SaveYear(SchoolYear* year);

Student StringToStudent(std::wstring str);
Course LoadDataCourse(std::string str);
Classes LoadDataClass(std::string str);
__int64 StringToInt(wchar_t*& ch);
__int64 StringToInt(std::wstring str);
Date StringToDate(wchar_t*& ch);
Date StringToDate(std::wstring str);
#endif // !Staff

