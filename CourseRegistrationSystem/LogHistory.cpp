//#include"CommonFunc.h"
//#include"Data.h"
//
//void SaveLogoutHistory(char* AccountUsername)
//{
//	__time32_t now = time(0);
//	char a[100];
//	_ctime32_s(a, &now);
//	std::ofstream file;
//	file.open("History\\logout.txt", std::ios::app);
//	file << AccountUsername << " " << a;
//	file.close();
//}
//
//void SaveCourseRegHis(char* AccountUsername, Course course)
//{
//	__time32_t now = time(0);
//	char a[100];
//	_ctime32_s(a, &now);
//	std::ofstream file;
//	file.open("History\\coursereg.txt", std::ios::app);
//	file << AccountUsername << " "<<course.ID<<" " << a;
//	file.close();
//}
//
//void SaveCourseCancelHis(char* AccountUsername, Course course)
//{
//	__time32_t now = time(0);
//	char a[100];
//	_ctime32_s(a, &now);
//	std::ofstream file;
//	file.open("History\\coursecancel.txt", std::ios::app);
//	file << AccountUsername << " "<<course.ID<<" " << a;
//	file.close();
//}
//
//void LoginStu()
//{
//	//clear the screen
//	char* U, *P;
//	U = new char[50];
//	P = new char[50];
//	do
//	{
//		std::cout << "Username: ";
//		std::cin >> U;
//		std::cout << "Password: ";
//		std::cin >> P;
//		// Read Account File
//		if (*U == *username && *P == *paswword){
//			//Go to Student
//		}
//		else std::cout << "Username or Password is invalid, please try again.";
//	} 	while (*U != *username && *P != *paswword);
//}