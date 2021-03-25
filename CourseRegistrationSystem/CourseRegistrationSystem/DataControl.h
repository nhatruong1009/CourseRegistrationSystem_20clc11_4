#ifndef DataControl
#define DataControl
#include"NewStructs.h"

void LoadClassInfo(Node*& Classes);
void LoadCourseInfo(Node*& Course);
void LoadScoreBoard(Node*& scoreboard);
void LoadYear(Node*& year);

void SaveClassInfo(Node* Classes);
void SaveCourseInfo(Node* Course);
void SaveScoreBoar(Node* scoreboard);
void SaveYear(Node* year);

#endif // !Staff

