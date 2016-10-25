//
//  Record/Date.cpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#include "Record/Date.hpp"
#include <iomanip>
#include <iostream>
#include <limits>
#include <ctime>

using namespace std;


Date::Date() : mYear(1970), mMonth(1), mDay(1) {
	
}

Date::Date(int year, int month, int day) : mYear(year), mMonth(month), mDay(day) {
	
}

Date::Date(FileReader* fr) {
	unsigned short year;
	fr->Read(&year, 2, 1);
	mYear = year;
	
	unsigned char month;
	fr->Read(&month, 1, 1);
	mMonth = month;
	
	unsigned char day;
	fr->Read(&day, 1, 1);
	mDay = day;
}

void Date::WriteToFile(FileWriter* fw) const {
	auto year = static_cast<unsigned short>(mYear);
	fw->Write(&year, 2, 1);
	
	auto month = static_cast<unsigned char>(mMonth);
	fw->Write(&month, 1, 1);
	
	auto day = static_cast<unsigned char>(mDay);
	fw->Write(&day, 1, 1);
}

Date Date::Today() {
	auto t = time(nullptr);
	auto today = localtime(&t);
	
	return {
		today->tm_year + 1900,
		today->tm_mon + 1,
		today->tm_mday,
	};
}

bool Date::Check() const {
	bool leapYear = (mYear % 4 == 0) && ((mYear % 100 != 0) || (mYear % 400 == 0));
	int days[12] = { 31, leapYear ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
	return (mYear != 0) && (1 <= mMonth && mMonth <= 12) && (1 <= mDay && mDay <= days[mMonth - 1]);
}

int Date::Days() const {
	int result = 0;
	
	bool leapYear = (mYear % 4 == 0) && ((mYear % 100 != 0) || (mYear % 400 == 0));
	int days[12] = { 31, leapYear ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int year = mYear - 1000;
	
	result += year * 365;
	result += year / 4 - year / 100 + year / 400 + 1;
	for(int i = 0; i < mMonth - 1; ++i) {
		result += days[i];
	}
	result += mDay;
	result -= 1;
	
	return result;
}

int operator -(const Date& lhs, const Date& rhs) {
	if(lhs.mYear * rhs.mYear < 0) {
		return lhs.Days() - rhs.Days() - 366;
	} else {
		return lhs.Days() - rhs.Days();
	}
}

void Date::InputFromCin() {
	// 年の入力
	while(true) {
		cout << "年> ";
		cin >> mYear;
		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		if(mYear != 0) {
			break;
		} else {
			cout << "入力が間違っています。\n\n";
		}
	}
	
	// 月の入力
	while(true) {
		cout << "月> ";
		cin >> mMonth;
		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		if(1 <= mMonth && mMonth <= 12) {
			break;
		} else {
			cout << "入力が間違っています。\n\n";
		}
	}
	
	// 日の入力
	bool leapYear = (mYear % 4 == 0) && ((mYear % 100 != 0) || (mYear % 400 == 0));
	int days[12] = { 31, leapYear ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
	while(true) {
		cout << "日> ";
		cin >> mDay;
		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		if(1 <= mDay && mDay <= days[mMonth - 1]) {
			break;
		} else {
			cout << "入力が間違っています。\n\n";
		}
	}
}

std::ostream& operator <<(std::ostream& os, const Date& rhs) {
	os << setfill('0') << setw(4) << rhs.mYear << "/";
	os << setfill('0') << setw(2) << rhs.mMonth << "/";
	os << setfill('0') << setw(2) << rhs.mDay;
	return os;
}
