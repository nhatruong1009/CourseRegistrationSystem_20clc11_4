#ifndef DataControl
#define DataControl
#include"NewStructs.h"

void LoadClassInfo(_Class*& Classes);
void LoadCourseInfo(_Course*& Course);
void LoadScoreBoard(Score*& scoreboard);
void LoadYear(SchoolYear*& year);

void SaveClassInfo(_Class* Classes);
void SaveCourseInfo(_Course* Course);
void SaveScoreBoar(Score* scoreboard);
void SaveYear(SchoolYear* year);

#endif // !Staff

