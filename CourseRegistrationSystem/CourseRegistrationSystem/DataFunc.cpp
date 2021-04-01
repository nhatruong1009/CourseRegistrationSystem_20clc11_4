#include"DataControl.h"
#include<string>
#include <fstream>
#include <locale>
#include <codecvt>
__int64 StringToInt(wchar_t*& ch) {
	wchar_t* temp = ch;
	unsigned __int64 a = 0;
	while (*temp!=L'\0')
	{
		a = a * 10 + *temp-L'0';
		temp++;
	}
	delete[] ch;
	return a;
}
__int64 StringToInt(std::wstring str) {
	unsigned __int64 a = 0;
	for (int i = 0; i < str.length(); i++) {
		a = a * 10 + str[i] - L'0';
	}
	return a;
}
int lengthStr(wchar_t* ch) {
	for (int i = 0;; i++) {
		if (ch[i] == L'\0') return i;
	}
}
Date StringToDate(wchar_t*& ch) {
	Date a;
	int beg = 0;
	int end = 0;
	while (ch[end]!=L'\0' && ch[end]!=L'/' )
	{
		end += 1;
	}
	if (ch[end] != L'\0') {
		for (; beg < end; beg++) {
			a.dd = a.dd * 10 + ch[beg]-L'0';
		}
		beg = end + 1;
		end += 1;
		while (ch[end] != L'\0' && ch[end] != L'/')
		{
			end += 1;
		}
		if (ch[end] != L'\0') {
			for (; beg < end; beg++) {
				a.mm = a.mm * 10 + ch[beg]-L'0';
			}
			beg = end + 1;
			end += 1;
			while (ch[end] != L'\0')
			{
				end += 1;
			}
			for (; beg < end; beg++) {
				a.yy = a.yy * 10 + ch[beg]-L'0';
			}
		}
	}
	delete[] ch;
	return a;
}
Date StringToDate(std::wstring str) {
	Date a;
	int beg = 0;
	int end = 0;
	while (str[end] != L'\0' && str[end] != L'/')
	{
		end += 1;
	}
	if (str[end] != L'\0') {
		for (; beg < end; beg++) {
			a.dd = a.dd * 10 + str[beg] - L'0';
		}
		beg = end + 1;
		end += 1;
		while (str[end] != L'\0' && str[end] != L'/')
		{
			end += 1;
		}
		if (str[end] != L'\0') {
			for (; beg < end; beg++) {
				a.mm = a.mm * 10 + str[beg] - L'0';
			}
			beg = end + 1;
			end += 1;
			while (str[end] != L'\0')
			{
				end += 1;
			}
			for (; beg < end; beg++) {
				a.yy = a.yy * 10 + str[beg] - L'0';
			}
		}
	}
	return a;
}
Student StringToStudent(std::wstring str) {
	//No, Student ID, First name, Last name, Gender, Date of Birth, Social ID
	Student stu;
	int beg = str.find(',')+1;
	int end = str.find(',', beg + 1);
	wchar_t* temp = new wchar_t[end - beg+1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	stu.account.username = new wchar_t[end - beg + 1];
	str.copy(stu.account.username, end - beg, beg);
	stu.account.username[end - beg  ] = '\0';
	stu.account.password = new wchar_t[7]{ L"123456" };
	stu.account.password[6] = '\0';
	stu.ID = StringToInt(temp);
	beg = end + 1;
	end = str.find(',', beg + 1);
	stu.firstname = new wchar_t[end - beg+1];
	str.copy(stu.firstname, end - beg, beg);
	stu.firstname[end - beg] = L'\0';
	beg = end + 1;
	end = str.find(',', beg + 1);
	stu.lastname = new wchar_t[end - beg+1];
	str.copy(stu.lastname, end - beg , beg);
	stu.lastname[end - beg] = L'\0';
	beg = end + 1;
	end = str.find(',', beg + 1);
	stu.gender = str[beg];
	beg = end + 1;
	end = str.find(',', beg + 1);
	temp = new wchar_t[end - beg+1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	stu.birth = StringToDate(temp);
	beg = end + 1;
	end = str.find(',', beg + 1);
	if (end == -1) {
		end = str.length();
	}
	temp = new wchar_t[end - beg+1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	stu.SocialID = StringToInt(temp);
	return stu;
};
void SaveStudent(_Student*stu,std::wstring filename){
	if (stu == nullptr) { return; }
	std::wfstream fi(filename, std::wfstream::binary | std::wfstream::out);
	fi.imbue(std::locale(fi.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	_Student *h = stu;
	int temp;
	do
	{
		std::wcout << fi.tellg() << " ";
		fi.write((wchar_t*)&stu->student.ID, sizeof(unsigned __int32)/2);
		
		temp = lengthStr(stu->student.firstname) + 1;
		fi.write((wchar_t*)&temp, sizeof(int)/2);
		fi.write((wchar_t*)&stu->student.firstname, temp);

		temp = lengthStr(stu->student.lastname) + 1;
		fi.write((wchar_t*)&temp, sizeof(int)/2);
		fi.write((wchar_t*)&stu->student.lastname,temp);

		fi.write((wchar_t*)&stu->student.gender, 1);

		fi.write((wchar_t*)&stu->student.birth, sizeof(Date)/2);

		fi.write((wchar_t*)&stu->student.SocialID, sizeof(unsigned __int32)/2);

		if (stu->student.coursenow == nullptr)
			temp = 0;
		else temp = _msize(stu->student.coursenow) / sizeof(wchar_t*);
		fi.write((wchar_t*)&temp, sizeof(int)/2);
		for (int i = 0; i < temp; i++) {
			int temp1 = lengthStr(stu->student.coursenow[i])+1;
			fi.write((wchar_t*)&temp1, sizeof(int)/2);
			fi.write((wchar_t*)stu->student.coursenow[i],temp1);
		}

		if (stu->student.allcourse == nullptr)
			temp = 0;
		else temp = _msize(stu->student.allcourse) / sizeof(wchar_t*);
		fi.write((wchar_t*)&temp, sizeof(int)/2);
		for (int i = 0; i < temp; i++) {
			int temp1 = lengthStr(stu->student.allcourse[i]) + 1;
			fi.write((wchar_t*)&temp1, sizeof(int)/2);
			fi.write((wchar_t*)stu->student.allcourse[i], temp1);
		}

		temp = lengthStr(stu->student.account.username)+1;
		fi.write((wchar_t*)&temp, sizeof(int)/2);
		fi.write((wchar_t*)stu->student.account.username,temp);

		temp = lengthStr(stu->student.account.password) + 1;
		fi.write((wchar_t*)&temp, sizeof(int)/2);
		fi.write((wchar_t*)stu->student.account.password,temp);

		fi.write((wchar_t*)&stu->student.GPA, sizeof(float)/2);

		stu = stu->pNext;
	} while (h != stu);
	fi.close();
}
_Student* LoadStudent(std::wstring filename) {
	 std::wfstream fi(filename, std::wfstream::binary | std::wfstream::in); 
	 fi.imbue(std::locale(fi.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	 if (!fi) { return nullptr; }
	 _Student* result = nullptr;
	 int temp;
	 fi.seekg(0, std::ios_base::end);
	 int end = fi.tellg();
	 end -= 2;
	 fi.seekg(0, std::ios_base::beg);
	 Student a;
	 while (fi.tellg()<=end)
	 {
		 std::wcout << fi.tellg()<<" ";
		 fi.read((wchar_t*)&a.ID, sizeof(__int32)/2);
		 fi.read((wchar_t*)&temp, sizeof(int)/2);
		 a.firstname = new wchar_t[temp];
		 fi.read((wchar_t*)&a.firstname[0],temp);
		 a.firstname[temp - 1] = L'\0';

		 fi.read((wchar_t*)&temp, sizeof(int)/2);

		 a.lastname = new wchar_t[temp];
		 fi.read((wchar_t*)&a.lastname[0],temp);

		 fi.read((wchar_t*)&a.gender, 1);

		 fi.read((wchar_t*)&a.birth, sizeof(Date)/2);

		 fi.read((wchar_t*)&a.SocialID, sizeof(unsigned __int32)/2);

		 fi.read((wchar_t*)&temp, sizeof(int)/2);

		 if (temp != 0) a.coursenow = new wchar_t* [temp];
		 for (int i = 0; i < temp; i++) {
			 int temp2;
			 fi.read((wchar_t*)&temp2, sizeof(int)/2);
			 if (temp2 != 0) {
				 a.coursenow[i] = new wchar_t[temp2];
				 fi.read((wchar_t*)a.coursenow[i], temp2);
			 }
		 }

		 fi.read((wchar_t*)&temp, sizeof(int)/2);
		 if (temp != 0) a.allcourse = new wchar_t* [temp];
		 for (int i = 0; i < temp; i++) {
			 int temp2;
			 fi.read((wchar_t*)&temp2, sizeof(int)/2);
			 if(temp2!=0)
			 { 
			 a.allcourse[i] = new wchar_t[temp2];
			 fi.read((wchar_t*)a.allcourse[i],temp2);
			 }
		 }

		 fi.read((wchar_t*)&temp, sizeof(int)/2);
		 a.account.username = new wchar_t[temp];
		 fi.read((wchar_t*)a.account.username, temp);

		 fi.read((wchar_t*)&temp, sizeof(int)/2);
		 a.account.password = new wchar_t[int(temp)];
		 fi.read((wchar_t*)a.account.password, temp);

		 fi.read((wchar_t*)&a.GPA, sizeof(float)/2);
		 PrintStu(&a);
		 AddStudent(result, a);
	 }
	 return result;
}