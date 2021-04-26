#include"CommonFunc.h"
#include"Data.h"


void ChangeInfo(Student*& CurrentUser);
void SaveLogoutHistory(char* AccountUsername)
{
	__time32_t now = time(0);
	char a[100];
	_ctime32_s(a, &now);
	std::ofstream file;
	file.open("History\\logout.txt", std::ios::app);
	file << AccountUsername << " " << a;
	file.close();
}

void SaveCourseRegHis(char* AccountUsername, Course course)
{
	__time32_t now = time(0);
	char a[100];
	_ctime32_s(a, &now);
	std::ofstream file;
	file.open("History\\coursereg.txt", std::ios::app);
	file << AccountUsername << " " << course.ID << " " << a;
	file.close();
}

void SaveCourseCancelHis(char* AccountUsername, Course course)
{
	__time32_t now = time(0);
	char a[100];
	_ctime32_s(a, &now);
	std::ofstream file;
	file.open("History\\coursecancel.txt", std::ios::app);
	file << AccountUsername << " " << course.ID << " " << a;
	file.close();
}

void LoginStu(Student*& CurrentUser)
{
	system("cls");	//clear the screen
	std::string U, P;
	if (std::cin.tellg() != 0) std::cin.clear();
	do
	{
		std::cout << "----------- Login -----------\n";
		std::cout << "Username: ";
		std::getline(std::cin, U);
		std::cout << "Password: ";
		P = InputHidden();
		if (P == "") { CurrentUser = 0; break; }// don't input password;
		std::string foldername = "K20";
		foldername = foldername + U[0] + U[1];
		Filelist* list = TakeFileInFolder("Data\\Grade\\" + foldername + "\\Student");
		if (list == nullptr)
		{
			system("cls");
			std::cout << "Username is invalid, please try again." << std::endl;
			continue;
		}
		Filelist* cur = list;
		// Read Account File
		do
		{
			if (U == cur->filename)
				break;
			cur = cur->pNext;
		} while (cur != list);
		if (U != cur->filename)
		{
			system("cls");
			std::cout << "Username is invalid, please try again." << std::endl;
			continue;
		}
		Student* a = BinToStu("Data\\Grade\\" + foldername + "\\Student\\" + cur->filename);
		if (P.compare(ToString(a->account.password)) == 0)
		{
			CurrentUser = a;
			SaveLoginHistory(a->account.username);
			break;
		}
		else { system("cls"); std::cout << "Password is invalid, please try again. " << std::endl; }
	} while (1);
	// Go to Student menu
}

void Logout(Student CurrentUser)
{
	system("cls");
	SaveLogoutHistory(CurrentUser.account.username);
	// Go to menu
}

void ChangePassword(Student* CurrentUser)
{

	system("cls");
	std::string pass1, pass2;
	do
	{
		std::cout << "New password: \t\t";
		pass1 = InputHidden();
		std::cout << "Confirm password: \t";
		pass2 = InputHidden();
		if (pass1 != pass2) std::cout << "Your password and confirmation password do not match, try again." << std::endl << std::endl;
	} while (pass1 != pass2);
	std::string foldername = "K20"; // 21st century, will update later when 22nd century come
	foldername = foldername + CurrentUser->account.username[0] + CurrentUser->account.username[1];
	CurrentUser->account.password = StrToChar(pass1);
	StuToBin(CurrentUser, "Data\\Grade\\" + foldername + "\\Student\\" + ToString(CurrentUser->account.username));
	short n;
	std::cout << "Change successfully " << std::endl;
	std::cout << "> Go back <";
	_getwch();
	ChangeInfo(CurrentUser);
}

void ChangeSocialID(Student* CurrentUser)
{
	system("cls");
	unsigned __int64 newSocialID1, newSocialID2;
	do
	{
		std::cout << "New Social ID:\t\t";
		newSocialID1 = InputNumber();
		std::cout << "Confirm new Social ID:\t";
		newSocialID2 = InputNumber();
		if (newSocialID1 != newSocialID2)
			std::cout << "New Social ID and Confirm Social ID do not match, try again " << std::endl << std::endl;
	} while (newSocialID1 != newSocialID2);
	std::cout << "Change succesfully " << std::endl;
	CurrentUser->SocialID = newSocialID1;
	std::string foldername = "K20"; // 21st century, will update later when 22nd century come
	foldername = foldername + CurrentUser->account.username[0] + CurrentUser->account.username[1];
	StuToBin(CurrentUser, "Data\\Grade\\" + foldername + "\\Student\\" + ToString(CurrentUser->account.username));
	short n;
	std::cout << "> Go back <";
	_getwch();
	ChangeInfo(CurrentUser);
}

void ChangeDOB(Student* CurrentUser)
{
	system("cls");
	Date dat;
	while (1)
	{
		std::cout << "Birth: ";
		dat = InputDate();
		if (dat.dd == 0) { dat = { 1,1,2000 }; }
		if (CheckDate(dat))
			break;
		else
		{
			std::cout << "Date is invalid, try again. " << std::endl << std::endl;
			continue;
		}
	}
	std::cout << "Change successfully " << std::endl;
	CurrentUser->birth = dat;
	std::string foldername = "K20"; // 21st century, will update later when 22nd century come
	foldername = foldername + CurrentUser->account.username[0] + CurrentUser->account.username[1];
	StuToBin(CurrentUser, "Data\\Grade\\" + foldername + "\\Student\\" + ToString(CurrentUser->account.username));
	short n;
	std::cout << "> Go back <";
	_getwch();
	ChangeInfo(CurrentUser);
}

void ChangeInfo(Student*& CurrentUser)
{
	system("cls");
	int num;
	char** menu = new char* [4];
	menu[0] = new char[] {"Password"};
	menu[1] = new char[] {"Date Of Birth"};
	menu[2] = new char[] {"Social ID"};
	menu[3] = new char[] {"Back"};
	switch (Menu(menu, 5, 2))
	{
	case 0:
		ChangePassword(CurrentUser);
		break;
	case 1:
		ChangeDOB(CurrentUser);
		break;
	case 2:
		ChangeSocialID(CurrentUser);
		break;
	case 3:
	case -1:
		return;
		// return to student mode
	}
}

_Student* SearchStu(unsigned __int64* ID) // Return LL _Student		// Use dynamic array of ID when using
{
	_Student* head = nullptr, * cur;
	head = new _Student;	// dummy node;
	cur = head;
	head->pNext = head->pPrev = nullptr;
	int n = _msize(ID)/8;
	for (int i = 0; i < n; i++)
	{
		if (ID[i] < 10)
			continue;
		std::string id = ToString(NumToStr(ID[i]));
		std::string foldername = "K20"; 
		foldername = foldername + id[0] + id[1];
		Filelist* list = TakeFileInFolder("Data\\Grade\\" + foldername + "\\Student");
		if (list == nullptr)
		{
			std::cout << id << " does not exist "<<std::endl;
		}
		Filelist* curlist = list;
		do
		{
			if (id == curlist->filename)
				break;
			curlist = curlist->pNext;
		} while (curlist != list);
		if (id != curlist->filename)
			std::cout << id << " does not exist " << std::endl;
		else
		{
			cur->pNext = new _Student;
			cur->pNext->pPrev = cur;
			cur = cur->pNext;
			cur->student = BinToStu("Data\\Grade\\" + foldername + "\\Student\\" + curlist->filename);
			cur->pNext = head;
			head->pPrev = cur;
		}
	}
	_Student* temp = head;
	head = head->pNext;
	cur->pNext = head;
	if (head)
		head->pPrev = cur;
	delete temp;	//delete dummy node
	return head;

	// REMEMBER TO DEALLOCATE WHEN FINISHED SEARCHING !!!
}

Student* SearchStu(unsigned __int64 ID) 
{
	if (ID < 10)
	{
		std::cout << ID << " does not exist " << std::endl;
		return nullptr;
	}
	std::string id = ToString(NumToStr(ID));
	std::string foldername = "K20";
	foldername = foldername + id[0] + id[1];
	Student* a = BinToStu("Data\\Grade\\" + foldername + "\\Student\\" + id);
	if (!a)
		std::cout << ID << " does not exist " << std::endl;
	return a;
}

Student** SearchStu(unsigned __int64* ID, int Grade)	// Use dynamic array of ID when using
{
	Student** a=nullptr;
	int n = _msize(ID) / 8;
	a = new Student * [n] {};
	std::string foldername = "K";
	foldername = foldername + NumToStr(Grade);
	for (int i = 0; i < n; i++)
	{
		a[i] = BinToStu("Data\\Grade\\" + foldername + "\\Student\\" + NumToStr(ID[i]));
		if (a[i] == nullptr)
		{
			std::cout << ID[i] << " does not exist " << std::endl;
		}
	}
	return a;

	// REMEMBER TO DEALLOCATE WHEN FINISHED SEARCHING !!!
}