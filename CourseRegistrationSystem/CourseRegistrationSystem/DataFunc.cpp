#include"DataControl.h"
#include<string>
#include <fstream>
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