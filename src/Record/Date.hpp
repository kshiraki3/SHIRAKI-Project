//
//  Record/Date.hpp
//  SHIRAKI Project
//
//  Created by 白木滉平 on 2016/10/20.
//  Copyright (c) 2016 SHIRAKI System. All rights reserved.
//

#ifndef Included_Record_Date_hpp
#define Included_Record_Date_hpp

#include "FileIO/FileReader.hpp"
#include "FileIO/FileWriter.hpp"
#include <ostream>


struct Date {
	Date();	// 1970年1月1日
	Date(int year, int month, int day);
	Date(FileReader* fr);	// ファイルから
	
	void WriteToFile(FileWriter* fw) const;
	
	static Date Today();	// 今日の日付
	
	bool Check() const;	// 値の妥当性をチェック
	
	int Days() const;	// 1000年1月1日からの経過日数
	friend int operator -(const Date& lhs, const Date& rhs);	// 日付の差を日数で返す
	
	// 比較
	bool operator ==(const Date& rhs) const;
	bool operator !=(const Date& rhs) const;
	bool operator >(const Date& rhs) const;
	bool operator <(const Date& rhs) const;
	bool operator >=(const Date& rhs) const;
	bool operator <=(const Date& rhs) const;
	
	void InputFromCin();	// キーボードから入力
	
	// レコード
	int mYear, mMonth, mDay;
};

std::ostream& operator <<(std::ostream& os, const Date& rhs);

#endif
