#ifndef DataControl
#define DataControl
#include"NewStructs.h"

void VietNamText();
void LoadClassInfo(_Class*& Classes);
void LoadCourseInfo(_Course*& Course);
void LoadScoreBoard(Score*& scoreboard);
void LoadYear(SchoolYear*& year);

void SaveClassInfo(_Class* Classes);
void SaveCourseInfo(_Course* Course);
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

